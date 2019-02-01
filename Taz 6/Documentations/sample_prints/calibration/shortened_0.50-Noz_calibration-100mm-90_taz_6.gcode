;  Shortened 0.50-Noz_calibration-100mm-90.gcode

M109 S235               ; heat nozzle
G21                     ; set units to millimeters
M82                     ; use absolute distances for extrusion
G92 E0                  ; Set extruder to 0
G1 E100 F90             ; Extrude 100mm
M400                    ; finish movement
M84                     ; disable motors
M300 S15 P55            ; buzzer
M117 Finished
