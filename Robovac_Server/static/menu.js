"use strict";
var mTimer;
var mMenu = ["overview",0];
var mIndex;


function getMenu(menu,sub)
{
  mMenu = [menu,sub];
  if (mXmlhttp.readyState != 4)
  {
    mXmlhttp.abort();
    mXmlhttp.onreadystatechange = function(){}
  }
  mXmlhttp = new XMLHttpRequest();
  mXmlhttp.open("GET","/menu?view="+menu+"&sub="+sub);
  mXmlhttp.send();
  mXmlhttp.setTimeout = 2000;
  mXmlhttp.onreadystatechange = parseMenu;
  mXmlhttp.timeout = onMenuTimeout;
}

function setActiveMenu(id)
{
  var topbar = document.getElementById("topbar");
  for (var i = 1; i < topbar.childElementCount-1; i++)
  {
    topbar.children[i].firstElementChild.removeAttribute("class");
  }
  var button = document.getElementById(id);
  button.setAttribute("class","active");
}

function setActiveSubMenu(pos)
{
  var sidemenu = document.getElementById("sidebar");
  for (var i=0; i<sidemenu.childElementCount; i++)
  {
    var frame = sidemenu.children[i];
    var text = frame.firstElementChild;
    frame.removeAttribute("class");
    text.removeAttribute("class");
    if (i == pos)
    {
      frame.setAttribute("class","SubMenuButtonActive");
      text.setAttribute("class","SubMenuButtonActiveText");
    }
    else
    {
      frame.setAttribute("class","SubMenuButton");
      text.setAttribute("class","SubMenuButtonText");
    }
  }
}

function onMenuTimeout()
{
  mTimer = setTimeout("getMenu("+mMenu[0]+","+mMenu[1]+")",5000)
}

function parseMenu()
{
  if (mXmlhttp.readyState == 4 && mXmlhttp.status == 200)
  {
    mIndex = mXmlhttp.responseXML.getElementsByTagName("menu")[0];
    var sidebar = document.getElementById("sidebar");
    if (mIndex.getElementsByTagName("sidebar")[0].getAttribute("hidden") != "true")
    {
      sidebar.style.display = "block";
      var sidebar_el = mIndex.getElementsByTagName("item");
      while (sidebar.hasChildNodes())
      {
        sidebar.removeChild(sidebar.childNodes[0]);
      }
      for (var i = 0; i < sidebar_el.length; i++)
      {
        var sidebar_menu = document.createElement("div");
        sidebar_menu.setAttribute("id",sidebar_el[i].getAttribute("id"));
        sidebar_menu.setAttribute("class","SubMenuButton")
        var sidebar_menu_a = document.createElement("a");
        sidebar_menu_a.setAttribute("href","#");
        sidebar_menu_a.setAttribute("class","SubMenuButtonText");
        sidebar_menu_a.appendChild(document.createTextNode(translate(sidebar_el[i].getAttribute("textref"),mLanguage)));
        sidebar_menu.appendChild(sidebar_menu_a);
        sidebar.appendChild(sidebar_menu);
        var sidebarclick = "setActiveSubMenu("+i+");show_"+mMenu[0]+"("+i+")";
        sidebar_menu.setAttribute("onclick",""+sidebarclick);
      }
    }
    else
    {
      sidebar.style.display = "none";
    }
    var menuname = mIndex.getAttribute("id");
    setActiveSubMenu(mMenu[1]);
    window["show_"+menuname](mMenu[1]);
  }
  else if (mXmlhttp.readyState == 4)
  {
    onMenuTimeout();
  }
}
