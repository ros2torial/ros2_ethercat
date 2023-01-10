

#include "ethercat_interface/ec_slave.hpp"
#include "ethercat_plugins/commondefs.hpp"
#include <iostream>

namespace ethercat_plugins
{

class Omron_FH_2050 : public ethercat_interface::EcSlave
{
public:
    Omron_FH_2050() : EcSlave(0x00000083, 0x000000fa) {}
    virtual ~Omron_FH_2050() {}
    virtual void processData(size_t index, uint8_t* domain_address){
        
        switch(index){
            case 0:
                EC_WRITE_BIT(domain_address, 0x00, trigger);
                trigger = false;
                break;
            case 1:
                data[1] = EC_READ_S32(domain_address);
                break;
            case 2:
                data[2] = EC_READ_S32(domain_address);
                break;
            case 3:
                data[3] = EC_READ_S32(domain_address);
                break;
            case 4:
                data[4] = EC_READ_S32(domain_address);
                break;
            default:
                std::cout << "WARNING. pdo index = "<<index <<" out of range." << std::endl;
        }

    }
    virtual const ec_sync_info_t* syncs() { return &syncs_[0]; }
    virtual size_t syncSize() {
        return sizeof(syncs_)/sizeof(ec_sync_info_t);
    }
    virtual const ec_pdo_entry_info_t* channels() {
        return channels_;
    }
    virtual void domains(DomainMap& domains) const {
        domains = domains_;
    }
    virtual bool setupSlave(
                std::unordered_map<std::string, std::string> slave_paramters,
                std::vector<double> * state_interface,
                std::vector<double> * command_interface){

        state_interface_ptr_ = state_interface;
        command_interface_ptr_ = command_interface;
        paramters_ = slave_paramters;
        return true;
    }

    virtual void initialize()
    {trigger = true;}

    virtual double get_data()
    {return double(data[2]);}
    
private:
    bool trigger = false; //false;
    int data[5] = {-1, -1, -1, -1, -1};
    // int sii_di_[16] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    // // digital write values
    // bool write_data_[16] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false};

    ec_pdo_entry_info_t channels_[165] = {
        {0x7000, 0x01, 1},
        {0x7000, 0x02, 1}, //Trigger camera 1
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x7000, 0x09, 1},
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x7000, 0x10, 1},
        {0x7000, 0x11, 1},
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x7001, 0x00, 32},
        {0x7002, 0x01, 32},
        {0x7002, 0x02, 32},
        {0x7002, 0x03, 32},
        {0x7002, 0x04, 32},
        {0x7010, 0x01, 1},
        {0x7010, 0x02, 1}, //Trigger camera 2
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x7010, 0x09, 1},
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x7010, 0x10, 1},
        {0x7010, 0x11, 1},
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x7011, 0x00, 32},
        {0x7012, 0x01, 32},
        {0x7012, 0x02, 32},
        {0x7012, 0x03, 32},
        {0x7012, 0x04, 32},
        {0x10f3, 0x04, 1},
        {0x0000, 0x00, 7}, /* Gap */
        {0x2002, 0x01, 8},
        {0x6000, 0x01, 1},
        {0x6000, 0x02, 1},
        {0x6000, 0x03, 1},
        {0x6000, 0x04, 1},
        {0x6000, 0x05, 1},
        {0x6000, 0x06, 1},
        {0x6000, 0x07, 1},
        {0x6000, 0x08, 1},
        {0x6000, 0x09, 1},
        {0x6000, 0x0a, 1},
        {0x6000, 0x0b, 1},
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x6000, 0x10, 1},
        {0x6000, 0x11, 1},
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x6001, 0x00, 32},
        {0x6002, 0x00, 32},
        {0x6003, 0x01, 32},
        {0x6004, 0x00, 32},
        {0x6005, 0x01, 32}, //Result Data 0 camera 1
        {0x6005, 0x02, 32}, //Result Data 1 camera 1
        {0x6005, 0x03, 32}, //Result Data 2 camera 1
        {0x6005, 0x04, 32}, //Result Data 3 camera 1
        {0x6005, 0x05, 32},
        {0x6005, 0x06, 32},
        {0x6005, 0x07, 32},
        {0x6005, 0x08, 32},
        {0x6010, 0x01, 1},
        {0x6010, 0x02, 1},
        {0x6010, 0x03, 1},
        {0x6010, 0x04, 1},
        {0x6010, 0x05, 1},
        {0x6010, 0x06, 1},
        {0x6010, 0x07, 1},
        {0x6010, 0x08, 1},
        {0x6010, 0x09, 1},
        {0x6010, 0x0a, 1},
        {0x6010, 0x0b, 1},
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x6010, 0x10, 1},
        {0x6010, 0x11, 1},
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x0000, 0x00, 1}, /* Gap */
        {0x6011, 0x00, 32},
        {0x6012, 0x00, 32},
        {0x6013, 0x01, 32},
        {0x6014, 0x00, 32},
        {0x6015, 0x01, 32}, //Result Data 0 camera 2
        {0x6015, 0x02, 32}, //Result Data 1 camera 2
        {0x6015, 0x03, 32}, //Result Data 2 camera 2
        {0x6015, 0x04, 32}, //Result Data 3 camera 2
        {0x6015, 0x05, 32},
        {0x6015, 0x06, 32},
        {0x6015, 0x07, 32},
        {0x6015, 0x08, 32},
    };
    ec_pdo_info_t pdos_[14] = {
        {0x1600, 32, channels_ + 0},
        {0x1601, 5, channels_ + 32},
        {0x1620, 32, channels_ + 37},
        {0x1621, 5, channels_ + 69},
        {0x1bfe, 2, channels_ + 74},
        {0x1bff, 1, channels_ + 76},
        {0x1a00, 32, channels_ + 77},
        {0x1a01, 3, channels_ + 109},
        {0x1a02, 1, channels_ + 112},
        {0x1a04, 8, channels_ + 113},
        {0x1a20, 32, channels_ + 121},
        {0x1a21, 3, channels_ + 153},
        {0x1a22, 1, channels_ + 156},
        {0x1a24, 8, channels_ + 157},
    };
    ec_sync_info_t syncs_[5] = {
        {0, EC_DIR_OUTPUT, 0, NULL, EC_WD_DISABLE},
        {1, EC_DIR_INPUT, 0, NULL, EC_WD_DISABLE},
        {2, EC_DIR_OUTPUT, 2, pdos_ + 0, EC_WD_ENABLE},
        {3, EC_DIR_INPUT, 6, pdos_ + 2, EC_WD_DISABLE},
        {0xff}
    };

    DomainMap domains_ = {
        {0, {1,113,114,115,116} }
    };


};

}  // namespace ethercat_plugins

#include <pluginlib/class_list_macros.hpp>

PLUGINLIB_EXPORT_CLASS(ethercat_plugins::Omron_FH_2050, ethercat_interface::EcSlave)
