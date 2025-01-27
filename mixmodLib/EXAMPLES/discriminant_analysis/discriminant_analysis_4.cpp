/***************************************************************************
                             EXAMPLES/discriminant_analysis/discriminant_analysis_4.cpp  description
    copyright            : (C) MIXMOD Team - 2001-2016
    email                : contact@mixmod.org
 ***************************************************************************/

/***************************************************************************
    This file is part of MIXMOD
    
    MIXMOD is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    MIXMOD is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with MIXMOD.  If not, see <http://www.gnu.org/licenses/>.

    All informations available on : http://www.mixmod.org                                                                                               
***************************************************************************/
#include <mixmod.h>
#include "mixmod/Kernel/IO/GaussianSample.h"
#include "mixmod/Utilities/ExampleDataUtil.h"

/**
 * @file heterogeneousDA.cpp
 * @brief Example for heterogeneous DA.
 * @author Parmeet Bhatia
 */

void discriminant_analysis_4_example () {

    cout<<"-----------------------------------------------------------------------"<<endl;
    cout<<"Heterogeneous discriminant analysis: "<<endl;
    cout<<"-----------------------------------------------------------------------"<<endl<<endl;

     // if mximod_example is installed in the /usr/local/bin folder, data files are in /usr/local/share/mixmod/EXAMPLES folder
    //otherwise, change the following line
    string basePath ("/usr/local/share/mixmod/EXAMPLES/data/");
    string learnFile("heterodata.train");
    string predictFile("heterodata.test");

    // XEM::LearnInput
    XEM::LearnInput * lInput = XEM::getLearnInput (basePath + learnFile);

    lInput->removeModelType ( 0 );
    lInput->addModel ( XEM::Heterogeneous_pk_E_L_B );
    lInput->addModel ( XEM::Heterogeneous_pk_E_Lk_B );
    lInput->addModel ( XEM::Heterogeneous_pk_E_L_Bk );
    lInput->addModel ( XEM::Heterogeneous_pk_E_Lk_Bk );
    lInput->addModel ( XEM::Heterogeneous_pk_Ek_L_B );
    lInput->addModel ( XEM::Heterogeneous_pk_Ek_Lk_B );
    lInput->addModel ( XEM::Heterogeneous_pk_Ek_L_Bk );
    lInput->addModel ( XEM::Heterogeneous_pk_Ek_Lk_Bk );
    lInput->addModel ( XEM::Heterogeneous_pk_Ej_L_B );
    lInput->addModel ( XEM::Heterogeneous_pk_Ej_Lk_B );
    lInput->addModel ( XEM::Heterogeneous_pk_Ej_L_Bk );
    lInput->addModel ( XEM::Heterogeneous_pk_Ej_Lk_Bk );
    lInput->addModel ( XEM::Heterogeneous_pk_Ekj_L_B );
    lInput->addModel ( XEM::Heterogeneous_pk_Ekj_Lk_B );
    lInput->addModel ( XEM::Heterogeneous_pk_Ekj_L_Bk );
    lInput->addModel ( XEM::Heterogeneous_pk_Ekj_Lk_Bk );
    lInput->addModel ( XEM::Heterogeneous_pk_Ekjh_L_B );
    lInput->addModel ( XEM::Heterogeneous_pk_Ekjh_Lk_B );
    lInput->addModel ( XEM::Heterogeneous_pk_Ekjh_L_Bk );
    lInput->addModel ( XEM::Heterogeneous_pk_Ekjh_Lk_Bk );
    /* : lInput->addModel(Heterogeneous model name:proportions fix */
    lInput->addModel ( XEM::Heterogeneous_p_E_L_B );
    lInput->addModel ( XEM::Heterogeneous_p_E_Lk_B );
    lInput->addModel ( XEM::Heterogeneous_p_E_L_Bk );
    lInput->addModel ( XEM::Heterogeneous_p_E_Lk_Bk );
    lInput->addModel ( XEM::Heterogeneous_p_Ek_L_B );
    lInput->addModel ( XEM::Heterogeneous_p_Ek_Lk_B );
    lInput->addModel ( XEM::Heterogeneous_p_Ek_L_Bk );
    lInput->addModel ( XEM::Heterogeneous_p_Ek_Lk_Bk );
    lInput->addModel ( XEM::Heterogeneous_p_Ej_L_B );
    lInput->addModel ( XEM::Heterogeneous_p_Ej_Lk_B );
    lInput->addModel ( XEM::Heterogeneous_p_Ej_L_Bk );
    lInput->addModel ( XEM::Heterogeneous_p_Ej_Lk_Bk );
    lInput->addModel ( XEM::Heterogeneous_p_Ekj_L_B );
    lInput->addModel ( XEM::Heterogeneous_p_Ekj_Lk_B );
    lInput->addModel ( XEM::Heterogeneous_p_Ekj_L_Bk );
    lInput->addModel ( XEM::Heterogeneous_p_Ekj_Lk_Bk );
    lInput->addModel ( XEM::Heterogeneous_p_Ekjh_L_B );
    lInput->addModel ( XEM::Heterogeneous_p_Ekjh_Lk_B );
    lInput->addModel ( XEM::Heterogeneous_p_Ekjh_L_Bk );
    lInput->addModel ( XEM::Heterogeneous_p_Ekjh_Lk_Bk );

    // Finalize
    lInput->finalize();

    // edit lInput
    cout<<"-----------------------------------------------------------------------"<<endl;
    cout<<" Input : "<<endl;
    cout<<"-----------------------------------------------------------------------"<<endl<<endl;
    lInput->edit ( cout );
    cout<<endl;


    // 2. XEM::LearnMain
    //---------------------

    // 2.1. Create XEM::ClusteringMain
    XEM::LearnMain lMain ( lInput );

    // 2.2 run XEM::LearnMain
    lMain.run();

    //2.3. Create a new XEM::LeranrOutput object
    XEM::LearnOutput * lOutput = lMain.getLearnOutput();


    // 3. post treatment example
    //------------------------------
    // sort (using CV - the default criterion)
    lOutput->sort ( XEM::CV );

    XEM::LearnModelOutput * lMOutput = NULL;

    // TODO: next 3 lines should not be needed (always use vector ?)
    int64_t* vLabel_p = lInput->getKnownLabelDescription()->getLabel()->getTabLabel();
    vector<int64_t> vLabel;
    for (int j=0; j<lInput->getNbSample(); j++) vLabel.push_back(vLabel_p[j]);

    if ( lOutput->atLeastOneEstimationNoError() ) {
        // get the best XEM::ClusteringModelOutput
        lMOutput = lOutput->getLearnModelOutput().front();
        XEM::ParameterDescription * paramDescription = lMOutput->getParameterDescription();

        cout<<"-----------------------------------------------------------------------"<<endl;
        cout<<"    LEARN STEP  "<<endl;
        cout<<"-----------------------------------------------------------------------"<<endl;
        cout<<endl;

        cout<<"-----------------------------------------------------------------------"<<endl;
        cout<<" Output : "<<endl;
        cout<<"-----------------------------------------------------------------------"<<endl<<endl;
        cout<<"-----------------------------------------------------------------------"<<endl;
        cout<<"Best model is (for CV criterion) "<<endl;
        cout<<"-----------------------------------------------------------------------"<<endl;
        cout<<"Best model is "<<endl;
        cout<<" - model : "<<* ( paramDescription->getModelType() ) <<endl;
        cout<<"-----------------------------------------------------------------------"<<endl<<endl;

        cout<<"-----------------------------------------------------------------------"<<endl;
        cout<<"Parameters display"<<endl;

        XEM::Parameter * param = paramDescription->getParameter();
        // print out parameters
        param->edit();

        // print out CV Label
        //std::cout << "CV Labels:" << std::endl;
        //lMOutput->getCVLabel()->getLabel()->edit(std::cout);
        std::cout << "CV Error Rate:" << ( 1-lMOutput->getCVLabel()->getLabel()->getErrorRate ( vLabel ) ) *100 << "%" << std::endl;

        int64_t ** classif = lMOutput->getCVLabel()->getLabel()->getClassificationTab ( vLabel, lMOutput->getNbCluster());
        std::cout << "CV Classification Tab:" << std::endl;
        for ( int i=0; i<lMOutput->getNbCluster(); i++ ) {
            std::cout << " | " ;
            for ( int j=0; j<lMOutput->getNbCluster()-1; j++ ) std::cout << classif[i][j] << " ";
            std::cout << classif[i][lMOutput->getNbCluster()-1] << "|" << std::endl;
        }

        // release memory
        for ( int i=0; i<lMOutput->getNbCluster(); i++ ) delete [] classif[i];
        delete [] classif;
    }


    cout<<"-----------------------------------------------------------------------"<<endl;
    cout<<"-----------------------------------------------------------------------"<<endl;
    cout<<"    PREDICT STEP  "<<endl;
    cout<<"-----------------------------------------------------------------------"<<endl;
    cout<<endl;

    //-------------------------------------------------------------------------------
    //Create Data Matrix

    // XEM::PredictInput
    XEM::PredictInput * pInput = XEM::getPredictInput(basePath + predictFile, lMOutput);
    pInput->finalize();
    // XEM::PredictMain
    XEM::PredictMain pMain ( pInput );
    pMain.run();

    // XEM::PredictOutput
    XEM::PredictOutput * pOutput = pMain.getPredictOutput();
    // get prediction model
    XEM::PredictModelOutput * pMOutput = pOutput->getPredictModelOutput().front();

    // print out labels
    std::cout << "Predict Labels:" << std::endl;
    pMOutput->getLabelDescription()->getLabel()->edit ( std::cout );
    // print out proba
    std::cout << "Predict Probas:" << std::endl;
    pMOutput->getProbaDescription()->getProba()->edit ( std::cout );



    //release memory
    delete lInput;
    delete pInput;
}
