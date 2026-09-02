#include "run.hh"

MyRunAction::MyRunAction()
{
        G4RunManager::GetRunManager()->SetPrintProgress(0);
        
        G4AccumulableManager* accMan = G4AccumulableManager::Instance();
        accMan->Register(totalFlux);
        accMan->Register(totalFlux2);
}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run* run)
{
        G4int runID = run->GetRunID();
        
        G4AccumulableManager* accMan = G4AccumulableManager::Instance();
        accMan->Reset();
        
        G4RunManager::GetRunManager()->SetRandomNumberStore(false);
}

void MyRunAction::EndOfRunAction(const G4Run* run)
{
        G4int runID = run->GetRunID();
        
        G4int nOfEvents = run->GetNumberOfEvent();
        if(nOfEvents == 0) return;
        
        G4AccumulableManager* accMan = G4AccumulableManager::Instance();
        accMan->Merge();
        
        G4double meanFlux = totalFlux.GetValue() / nOfEvents;
        G4double meanFlux2 = totalFlux2.GetValue() / nOfEvents;
        G4double var = meanFlux2 - meanFlux * meanFlux;
        G4double err = std::sqrt(std::max(0.0, var) / nOfEvents);
        
        std::ostringstream runFileName;
        runFileName << "output_Run" << runID << ".txt"; // nume fisiere de output dupa fiecare Run
        
        std::ofstream runOutputFile(runFileName.str());
        runOutputFile << "========== REZULTAT RUN" << runID << " ==========\n";
        runOutputFile << "Fluenta de neutroni:\n";
        //runOutputFile << G4BestUnit(meanFlux, "Per Unit Surface") << "\n\n";  // ca sa verific daca cm^-2 pus de mine mai jos este unitatea buna
        runOutputFile << meanFlux * 100 << " +/- " << err * 100 << " [n/cm2/NPS]\n\n";  // meanFlux default e in mm^-2
        runOutputFile << "H*(10) cu factorul de conv. fluenta->H*(10) pt. sursa AmBe ISO 8529:\n";
        runOutputFile << meanFlux * 39100 << " +/- " << err * 39100 << " [pSv/NPS]\n";
        runOutputFile.close();
}
