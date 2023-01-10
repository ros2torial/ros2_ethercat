#include <pluginlib/class_loader.hpp>
#include <ethercat_interface/ec_slave.hpp>

int main(int argc, char** argv)
{
  // To avoid unused parameter warnings
  (void) argc;
  (void) argv;

  pluginlib::ClassLoader<ethercat_interface::EcSlave> ecat_loader("ethercat_interface", "ethercat_interface::EcSlave");

  try
  {
    std::shared_ptr<ethercat_interface::EcSlave> camera = ecat_loader.createSharedInstance("ethercat_plugins::Omron_FH_2050");
    camera->initialize();


    printf("Triangle area: %.2f\n", camera->get_data());
  }
  catch(pluginlib::PluginlibException& ex)
  {
    printf("The plugin failed to load for some reason. Error: %s\n", ex.what());
  }

  return 0;
}