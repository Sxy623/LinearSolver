NAME Maros
ROWS
 N  OBJ
 L  RES1    
 L  RES2    
 E  BALANCE 
COLUMNS
    VOL1      OBJ       4.5
    VOL1      RES1      1
    VOL1      BALANCE   2.5
    VOL2      OBJ       2.5
    VOL2      RES2      1.5
    VOL2      BALANCE   2
    VOL3      OBJ       4
    VOL3      RES1      1
    VOL3      RES2      0.5
    VOL3      BALANCE   3
    VOL4      OBJ       4
    VOL4      RES1      1.5
    VOL4      RES2      0.5
    VOL4      BALANCE   2
    MPS_RgBALANCE  BALANCE   1
RHS
    RHS1      RES1      40
    RHS1      RES2      30
    RHS1      BALANCE   105
BOUNDS
 LO BND1      VOL3      -10
 UP BND1      VOL3      20
 UP BND1      VOL4      25
 UP BND1      MPS_RgBALANCE  10
ENDATA
