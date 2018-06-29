
mPCUSTATE = "stop";
mPCUMODE = "controlled";


#-------------------------------------------------------------------------------
#                           SET AND GET PCU_SETTINGS
#-------------------------------------------------------------------------------
def pcu_setState(state):
    global mPCUSTATE;
    mPCUSTATE = state;
return

def pcu_setMode(mode):
    global mPCUMODE;
    mPCUMODE = mode;
return

def pcu_getState():
return mPCUSTATE;

def pcu_getMode():
return mPCUMODE;
#-------------------------------------------------------------------------------
#-------------------------------------------------------------------------------
