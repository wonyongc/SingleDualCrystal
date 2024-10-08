#ifndef EXAMPLES_SingleDualCrystal_SRC_DualCrystalCalorimeterHIT_H
#define EXAMPLES_SingleDualCrystal_SRC_DualCrystalCalorimeterHIT_H

/// Framework include files
#include "DDG4/Geant4Data.h"
#include "G4OpticalPhoton.hh"
#include "G4VProcess.hh"


typedef ROOT::Math::XYZVector Position;
typedef ROOT::Math::XYZVector Direction;


namespace CalVision {

    const int finenbin=6000;
    const int coarsenbin=40;

  /// This is the hit definition.
  /** I took here the same definition of the default Geant4Tracker class,
   *  (see DDG4/Geant4Data.h)  but it could be anything else as well.
   *
   *  Please note:
   *  ============
   *  The MC truth handling as implemented in the Geant4ParticleHandler
   *  will not work with this class if the object(s) are saved with 
   *  the standard Geant4Output2ROOT event action. If the hit is 
   *  specialized, the output writing also must be specialized if
   *  MC truth handling should be supported.
   *  Otherwise it is sufficient to provide a ROOT dictionary as long as the
   *  base class dd4hep::sim::Geant4HitData is kept.
   *
   *  \author  M.Frank
   *  \version 1.0
   *  \ingroup DD4HEP_SIMULATION
   */
  class DualCrystalCalorimeterHit : public dd4hep::sim::Geant4Calorimeter::Hit   {

  public:
    int ncerenkov,nscintillator;
    float wavelenmin=300;
    float wavelenmax=1000;
    int nfinebin=finenbin;
    float timemin=0;
    float timemax=300;
    std::array<int,finenbin>  ncerwave;
    std::array<int,finenbin> nscintwave;
    std::array<int,finenbin>  ncertime;
    std::array<int,finenbin> nscinttime;
    float xmax=10;
    float ymax=10;
    float xmin=-10;
    float ymin=-10;
    int ncoarsebin=coarsenbin;
    std::array<std::array<int,coarsenbin>,coarsenbin> cerhitpos;
    std::array<std::array<int,coarsenbin>,coarsenbin> scinthitpos;



  public:
    /// Default constructor
    DualCrystalCalorimeterHit() = default;
    
    /// Initializing constructor
    DualCrystalCalorimeterHit(const Position& cell_pos):dd4hep::sim::Geant4Calorimeter::Hit(cell_pos),ncerenkov(0),nscintillator(0) {

      for( int i=0; i<finenbin; i++) {

        ncerwave[i]=0;
        nscintwave[i]=0;
        ncertime[i]=0;
        nscinttime[i]=0;
      }

      for( int i=0; i<coarsenbin; i++ ) {
  
        for( int j=0; j<coarsenbin; j++ ) {
  
          cerhitpos[i][j]=0;
          scinthitpos[i][j]=0;
  
        } 
      }
    }

    /// Default destructor
    virtual ~DualCrystalCalorimeterHit() = default;

    /// Assignment operator
    //DualCrystalCalorimeterHit& operator=(const DualCrystalCalorimeterHit& c);
  };

  /// Helper to dump data file
  /**
   *  Usage:  
   *  $> root.exe
   *  ....
   *  root [0] gSystem->Load("libDDG4Plugins.so");
   *  root [1] gSystem->Load("libDDG4_MySensDet.so");
   *  root [2] CalVision::Dump::dumpData(<num-ebents>,<file-name>);
   *
   */
  class Dump   {
  public:
    /// Standalone function to dump data from a root file
    static int DualCrystalCalorimeterdumpData(int num_evts, const char* file_name);

  };

}

// CINT configuration
#if defined(__CINT__) || defined(__MAKECINT__) || defined(__CLING__) || defined(__ROOTCLING__)
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

/// Define namespaces
#pragma link C++ namespace dd4hep;
#pragma link C++ namespace dd4hep::sim;
#pragma link C++ namespace CalVision;
#pragma link C++ class     CalVision::DualCrystalCalorimeterHit+;
#pragma link C++ class     CalVision::DualCrystalCalorimeterDump;
#endif

#endif // EXAMPLES_SingleDualCrystal_SRC_DualCrystalCalorimeterHIT_H
