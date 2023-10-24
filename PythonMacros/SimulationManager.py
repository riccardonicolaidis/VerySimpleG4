import os
import shutil as sh
import numpy as np

def Simulation():
    
    BasePath = "/home/riccardo/Documenti/NUSES/NUSES_LEM_RadiationEnvironment/SIMULATION_DoseAl"
    
    
    TkAl_0 = 0.01
    TkAl_1 = 8
    N = 30
    
    # Generate a Log spaced array of N values
    
    TkAl_array = np.logspace(np.log10(TkAl_0), np.log10(TkAl_1), N)
    
    
    src = os.path.join(BasePath, "src")
    include = os.path.join(BasePath, "include")
    build = os.path.join(BasePath, "build")
    DST = os.path.join(BasePath, "DST")
    macros = os.path.join(BasePath, "macros")
    
    globals_file = ""
    for file in os.listdir(include):
        if "Globals" in file:
            globals_file = os.path.join(include,file)
            print(globals_file)
            break
    
    # Se DST non esiste creala
    if not os.path.exists(DST):
        os.mkdir(DST)
    else:
        sh.rmtree(DST)
        os.mkdir(DST)
        
        
        
    for i in range(len(TkAl_array)):
        # Overwrite the globals file
        os.remove(globals_file)
        with open(globals_file, "w") as f:
            f.write("#ifndef GLOBALS_H\n")
            f.write("#define GLOBALS_H\n")
            f.write("#define TK_AL " + str(TkAl_array[i]) + "\n")
            f.write("#endif")
            
            
        # Create a new ruunPy.mac (delete and write)
        if os.path.exists(os.path.join(macros, "runPy.mac")):
            os.remove(os.path.join(macros, "runPy.mac"))
           
        
        FileContent = '''
/gps/verbose 0
/gps/ene/type Lin
/gps/ene/gradient 0
/gps/ene/intercept 1 
/gps/position 0 0 0 cm
/gps/direction 0 0 1

/GeneralPurpose/TkAluminium {}
/GeneralPurpose/TkSilicon 0.1
/run/reinitializeGeometry


/gps/particle e- 
/gps/ene/min 0.01 MeV
/gps/ene/max 20 MeV
/NameOfFile/NameOfFile Al_{}_e


/run/beamOn 5000000

/gps/particle proton
/gps/ene/min 0.01 MeV
/gps/ene/max 300 MeV
/NameOfFile/NameOfFile Al_{}_p


/run/beamOn 5000000
        
        '''.format(TkAl_array[i], TkAl_array[i], TkAl_array[i])
        
        
        with open(os.path.join(macros, "runPy.mac"), "w") as f:
            f.write(FileContent)
            
        # Compile
        if os.path.exists(build):
            sh.rmtree(build)
            os.mkdir(build)
        else:
            os.mkdir(build)
            
        os.chdir(build)
        os.system("cmake ..")
        os.system("make -j8")
        
        os.system("./Simulation runPy.mac")
        
        for file in os.listdir(build):
            if ".root" in file:
                sh.move(os.path.join(build, file), os.path.join(DST, file))
            
        
    
        






if __name__ == "__main__":
    Simulation()