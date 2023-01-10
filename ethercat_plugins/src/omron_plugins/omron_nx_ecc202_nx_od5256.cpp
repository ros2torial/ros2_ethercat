
#include "ethercat_interface/ec_slave.hpp"
#include "ethercat_plugins/commondefs.hpp"
#include <iostream>

namespace ethercat_plugins
{

class Omron_NX_ECC202_NX_OD5256 : public ethercat_interface::EcSlave
{
public:
    Omron_NX_ECC202_NX_OD5256() : EcSlave(0x00000083, 0x000000a6) {}
    virtual ~Omron_NX_ECC202_NX_OD5256() {}
    virtual void processData(size_t index, uint8_t* domain_address){
        uint16_t digital_out_;
	    digital_out_ = 0;
        for(auto i=0ul;i<16;i++){
            if(cii_do_[i] >= 0){
                if(!std::isnan(command_interface_ptr_->at(cii_do_[i]))){
                    write_data_[i] = (command_interface_ptr_->at(cii_do_[i])) ? true : false;
                    if(sii_do_[i] >= 0)
                        state_interface_ptr_->at(sii_do_[i]) = command_interface_ptr_->at(cii_do_[i]);
                }
            }
        }

	    // bit masking to get individual input values
        digital_out_ += ( write_data_[0] << 0 ); // bit 0
        digital_out_ += ( write_data_[1] << 1 ); // bit 1
        digital_out_ += ( write_data_[2] << 2 ); // bit 2
        digital_out_ += ( write_data_[3] << 3 ); // bit 3
        digital_out_ += ( write_data_[4] << 4 ); // bit 4
        digital_out_ += ( write_data_[5] << 5 ); // bit 5
        digital_out_ += ( write_data_[6] << 6 ); // bit 6
        digital_out_ += ( write_data_[7] << 7 ); // bit 7
        digital_out_ += ( write_data_[8] << 8 ); // bit 8
        digital_out_ += ( write_data_[9] << 9 ); // bit 9
        digital_out_ += ( write_data_[10] << 10 ); // bit 10
        digital_out_ += ( write_data_[11] << 11 ); // bit 11
        digital_out_ += ( write_data_[12] << 12 ); // bit 12
        digital_out_ += ( write_data_[13] << 13 ); // bit 13
        digital_out_ += ( write_data_[14] << 14 ); // bit 14
        digital_out_ += ( write_data_[15] << 15 ); // bit 15

	    EC_WRITE_U16(domain_address , digital_out_);
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

        for(auto index = 0ul; index < 16; index++){
            if(paramters_.find("do."+std::to_string(index))!= paramters_.end()){
                if(paramters_.find("command_interface/"+paramters_["do."+std::to_string(index)]) != paramters_.end())
                    cii_do_[index] = std::stoi(paramters_["command_interface/"+paramters_["do."+std::to_string(index)]]);
                if(paramters_.find("state_interface/"+paramters_["do."+std::to_string(index)]) != paramters_.end())
                    sii_do_[index] = std::stoi(paramters_["state_interface/"+paramters_["do."+std::to_string(index)]]);
            }
        }
        return true;
    }

private:
    int cii_do_[16] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    int sii_do_[16] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    // digital write values
    bool write_data_[16] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false};

    ec_pdo_entry_info_t channels_[1] = {
        {0x7022, 0x01, 16}, /* Output */
    };
    ec_pdo_info_t pdos_[1] = {
        {0x1604, 1, channels_ + 0}, /* Channel 1 */
    };
    ec_sync_info_t syncs_[2] = {
        {2, EC_DIR_OUTPUT, 1, pdos_ + 0, EC_WD_DISABLE},
        {0xff}
    };
    DomainMap domains_ = {
        {0, {0} }
    };
};

}  // namespace ethercat_plugins

#include <pluginlib/class_list_macros.hpp>

PLUGINLIB_EXPORT_CLASS(ethercat_plugins::Omron_NX_ECC202_NX_OD5256, ethercat_interface::EcSlave)
