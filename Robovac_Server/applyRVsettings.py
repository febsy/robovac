#import telnet_connection as TN
import subprocess as SP
import json as JSON

def reloadRVSettings(id):
  if id == "TIMESYNC":
      settingsfile = open('./static/settings.json')
      data = JSON.load(settingsfile)
      value = JSON.loads(JSON.dumps(data[id]).translate(None,'[]'))
      innervalue = JSON.dumps(value["VALUE"]).translate(None,'""')
      SP.call(['./static/setTime.sh',innervalue])
      settingsfile.close()
  #elif id == "NETWORK":
  return
