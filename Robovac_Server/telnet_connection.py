import sys
import telnetlib

mHOST = "0.0.0.0";
mConn;

def telnet_Init(HOST):
    global mConn;
    mConn = telnetlib.Telnet(HOST);
return;

def telnet_SendAndReceive(msg):
    global mConn;
    mConn.write(msg);
    answer = mConn.read_until("\n",1000);
return answer;


def telnet_Close():
    global mConn;
    mConn.close(mConn)
return;
