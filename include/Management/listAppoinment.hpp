#ifndef LISTAPPOINMENT_HPP
#define LISTAPPOINMENT_HPP

#include "Management/Appoinment.hpp"
#include "Template/Map.hpp"
#include "Template/LinkedList.hpp"
#include <map>
#include <Header/Header.hpp>

#include "Management/Date.hpp"
class listAppoinment : public map<Date, LinkedList<Appoinment>>
    {
    public:
        //* Constructor & Destructor
        listAppoinment();
        //* Methods
        void addAppointment(Appoinment* &app);
        // void removeAppointment(const string &ID);
        bool readAppointmentsFromFile();
        bool writeAppointmentsToFile();

        //* Getter
        vector<Appoinment*> getAppointmentsByDateRange(const string &startDate, const string &endDate);
        vector<Appoinment*> getAppointmentsByPatientIDIRange(const string &patientID, const string &startDate, const string &endDate);
        
        bool updateAppoinmentStatus(const string &ID, const bool &status, const bool &isProcessed);


    };
#endif