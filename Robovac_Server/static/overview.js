"use strict";


function show_overview(sub)
{
  var mBody = document.getElementById("main_body");
  while (mBody.childElementCount > 0)
  {
    mBody.removeChild(mBody.firstChild);
  }
  var overview_body = document.createElement("div");
  overview_body.setAttribute("class","Overview_body");
  mBody.appendChild(overview_body);
}
