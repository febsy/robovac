from flask import Flask, Response, request
import xml.etree.ElementTree as ET
import json as JSON
import ast as AST
import applyRVsettings as RVS
app = Flask(__name__)

# Sendet index.html (DEBUGGING ONLY)
@app.route('/')
def index():
    return app.send_static_file('index.html')

@app.route('/config', methods=['GET', 'POST', 'PUT'])
def req_handler():
    if request.method == 'GET':
        id = request.args.get('id', "", type=str)
        settingsfile = open('./static/settings.json')
        data = JSON.load(settingsfile)
        if id in data:
            resp = JSON.dumps(data[id])
            settingsfile.close()
        else:
            response = "Setting "+id+" not found"
            settingsfile.close()
            return response, 400
    elif request.method == 'PUT':
        id = request.args.get('id', "", type=str)
        settingsfile = open('./static/settings.json','r')
        data = JSON.load(settingsfile)
        settingsfile.close()
        if id in data:
            tmp = data
            settingsfile2 = open('./static/settings.json','w')
            newval = AST.literal_eval("["+request.data+"]")
            data[id] = newval
            JSON.dump(data,settingsfile2)
            settingsfile2.close()
            response = "OK"
            RVS.reloadRVSettings(id)
            return response
        else:
            response = "Setting "+id+" not found"
            return response, 400
    else:
        resp = '<value>no GET request</value>'
    return Response(resp, mimetype='json')

@app.route('/menu', methods=['GET'])
def menu_builder():
    menu = request.args.get('view',"overview", type=str)
    sub = request.args.get('sub',"0", type=str)
    tree = ET.parse('./static/menu.xml')
    root = tree.getroot();
    resp = '<menu/>'
    for n in root.iter('menu'):
        if n.attrib.get("id") == menu:
            resp = ET.tostring(n, encoding='utf8', method='xml')
    return Response(resp, mimetype='text/xml')
