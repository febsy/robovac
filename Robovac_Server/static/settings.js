"use strict";
var mItem;
var mTimer;
var mId;
var mSettingobject;

function show_settings(sub)
{
  mMenu[1] = sub;
  var mBody = document.getElementById("main_body");
  while (mBody.childElementCount > 0)
  {
    mBody.removeChild(mBody.firstChild);
  }
  var overview_body = document.createElement("div");
  overview_body.setAttribute("class","Overview_body");
  overview_body.setAttribute("id","Settings_body")
  mBody.appendChild(overview_body);
  mItem = mIndex.getElementsByTagName("item")[sub];
  if (mXmlhttp.readyState != 4)
  {
    mXmlhttp.abort();
    mXmlhttp.onreadystatechange = function(){}
  }
  mXmlhttp = new XMLHttpRequest();
  mXmlhttp.open("GET","/config?id="+(mItem.children[0].textContent));
  mXmlhttp.send();
  mXmlhttp.setTimeout = 2000;
  mXmlhttp.onreadystatechange = onSettings;
  mXmlhttp.timeout = onSettingsTimeout;
}

function onSettingsTimeout()
{
  show_settings(mMenu[1]);
}

function onSettings()
{
  if (mXmlhttp.readyState == 4 && mXmlhttp.status == 200)
  {
    mSettingobject = JSON.parse(mXmlhttp.response)[0];
    var body = document.getElementById("Settings_body");
    var settingsform = document.createElement("form");
    settingsform.setAttribute("class","SubMenuItem");
    var settingstitle = document.createElement("label");
    settingstitle.setAttribute("class","SubMenuItemLabel");
    settingstitle.textContent = translate(mItem.getAttribute("textref"),mLanguage);
    settingsform.appendChild(settingstitle);
    body.appendChild(settingsform);
    switch (mSettingobject["TYPE"]) {
      case "ENUM":
        var setting = document.createElement("select");
        setting.setAttribute("class","SubMenuItemSelect");
        setting.setAttribute("id","setting_dialog");
        for (var i = 0; i < mSettingobject["CASES"].length;i++)
        {
          var option = document.createElement("option");
          option.setAttribute("value",""+i);
          option.textContent = mSettingobject["CASES"][i];
          if (i == Number(mSettingobject["VALUE"]))
          {
            option.setAttribute("selected","true");
          }
          setting.appendChild(option);
        }
        var id = mItem.children[0].textContent;
        mId = id;
        var fcnt = "putSetting('"+id+"')"
        setting.setAttribute("onchange",""+fcnt)
        settingsform.appendChild(setting);
        break;
      default:
        var setting = document.createElement("input");
        setting.setAttribute("id","setting_dialog");
        setting.setAttribute("type","text");
        setting.setAttribute("class","SubMenuItemTextfield");
        setting.value = mSettingobject["VALUE"];
        var id = mItem.children[0].textContent;
        mId = id;
        var fcnt = "putSetting('"+id+"')"
        setting.setAttribute("onchange",""+fcnt)
        settingsform.appendChild(setting);
        break;
    }

  }
  else if (mXmlhttp.readyState == 4)
  {
    mTimer = setTimeout("onSettingsTimeout()",2000);
  }
}

function putSetting(id)
{
  var new_setting = document.getElementById("setting_dialog").value;
  var newsettingobject = mSettingobject;
  newsettingobject["VALUE"] = new_setting;
  var responseJSON = JSON.stringify(newsettingobject);
  if (mXmlhttp.readyState != 4)
  {
    mXmlhttp.abort();
    mXmlhttp.onreadystatechange = function(){}
  }
  mXmlhttp = new XMLHttpRequest();
  mXmlhttp.open("PUT","/config?id="+id);
  mXmlhttp.send(responseJSON);
  mXmlhttp.setTimeout = 2000;
  mXmlhttp.onreadystatechange = onSettingPut;
  mXmlhttp.timeout = onSettingPutTimeout;
}

function onSettingPutTimeout()
{
  putSetting(mId);
}

function onSettingPut()
{
  if (mXmlhttp.readyState == 4 && mXmlhttp.status == 200)
  {
    getLanguageSetting();
  }
  else if (mXmlhttp.readyState == 4)
  {
    mTimer = setTimeout("onSettingPutTimeout()",2000);
  }
}
