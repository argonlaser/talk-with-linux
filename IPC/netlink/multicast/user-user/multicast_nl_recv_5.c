#include <sys/socket.h>
#include <linux/netlink.h>
#include <stdio.h>
#include <malloc.h>
#include <stdio.h>

#define NLINK_MSG_LEN 1024

int main() {
  int fd = socket(PF_NETLINK, SOCK_RAW, NETLINK_GENERIC);
  printf("Inside recv main\n");

  if (fd < 0) {
    printf("Socket creation failed. try again\n");
    return -1;
  }

  struct sockaddr_nl src_addr;
  struct sockaddr_nl dest_addr;
  //allocate buffer for netlink message which
  //is message header + message payload
  struct nlmsghdr *nlh =(struct nlmsghdr *) malloc(NLMSG_SPACE(NLINK_MSG_LEN));
  //fill the iovec structure
  struct iovec iov;
  //define the message header for message
  struct msghdr msg;

  nlh->nlmsg_len = NLMSG_SPACE(NLINK_MSG_LEN);
  nlh->nlmsg_pid = getpid();   //src application unique id
  nlh->nlmsg_flags = 0;

  src_addr.nl_family = AF_NETLINK;   //AF_NETLINK socket protocol
  src_addr.nl_pid = getpid();   //application unique id
  src_addr.nl_groups = (1 << 5);   // specify the address which the process want to receive
                                               // if two or more address then turn on those bits
                                               // subscribe to 5 multicast address
  printf("Listening to the MCAST address (5): %d\n", src_addr.nl_groups);
  //attach socket to unique id or address
  bind(fd, (struct sockaddr *)&src_addr, sizeof(src_addr));

  iov.iov_base = (void *)nlh;   //netlink message header base address
  iov.iov_len = nlh->nlmsg_len;   //netlink message length


  msg.msg_name = (void *)&dest_addr;
  msg.msg_namelen = sizeof(dest_addr);
  msg.msg_iov = &iov;
  msg.msg_iovlen = 1;

  /* Listen forever in a while loop */
  while (1) {
    //receive the message
    recvmsg(fd, &msg, 0);
    printf("Received message: %s\n", (char *)NLMSG_DATA(nlh));
  }
  close(fd); // close the socket
}
