"use strict";

var labeltexts = {"label.startstop":["start/stop","Start/Stop"],
                  "label.pause":["pause","Pause"],
                  "label.calibrate":["Calibrate","Kalibrieren"],
                  "label.viewroom":["Show rooms","Zimmer anzeigen"],
                  "label.removeroom":["Remove roomdata","Zimmerdaten löschen"],
                  "label.uploadroom":["Upload roomdata","Zimmerdaten hochladen"],
                  "label.language":["Language","Sprache"],
                  "label.connection":["Connection","Netzwerk"],
                  "label.timesync":["Time synchronisation","Zeitsynchronisation"],
                  "label.energy":["Energy settings","Energieeinstellungen"],
                  "label.main":["Overview","Übersicht"],
                  "label.rooms":["Rooms","Zimmer"],
                  "label.console":["Terminal","Terminal"],
                  "label.settings":["Settings","Einstellungen"]
                };

function translate(label,languagecode)
{
  return window["labeltexts"][label][languagecode];
}
