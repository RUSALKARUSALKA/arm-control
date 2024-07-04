#include "arm_servos/servos_driver.h"

BaseRun::BaseRun(std::string nodeName) : Node(nodeName)
{
    RCLCPP_INFO(this->get_logger(), "%s node startup success.", nodeName.c_str());
    this->declare_parameter("moto_one_pose", moto_one_pose);     /*声明参数*/
    this->get_parameter("moto_one_pose", moto_one_pose); /*获取参数*/
    base_timer = this->create_wall_timer(200ms, std::bind(&BaseRun::base_timer_callback, this));
    //base_timer ->cancel();

    try
    {
        serial_.setPort("/dev/ttyUSB0");                            //选择要开启的串口号
        serial_.setBaudrate(115200);                                     //设置波特率
        serial::Timeout timeOut = serial::Timeout::simpleTimeout(2000);  //超时等待
        serial_.setTimeout(timeOut);                     
        serial_.open();                                                  //开启串口
    }
    catch (serial::IOException &e)
    {
        RCLCPP_ERROR(this->get_logger(), "bbtBot serial open failed!"); 
    }

    if (serial_.isOpen())
    {
        RCLCPP_INFO(this->get_logger(), "bbtBot serial open success!"); 
        serial_thread_ = std::shared_ptr<std::thread>(
            new std::thread(std::bind(&BaseRun::readSerialData, this)));
    }
}

BaseRun::~BaseRun()
{
    serial_.close();
    RCLCPP_INFO(this->get_logger(), "bbtBot serial close success!"); 
}
void BaseRun::base_timer_callback()
{
    this->get_parameter("moto_one_pose", moto_one_pose); 
    if(moto_one_pose >499 && moto_one_pose < 2501)
        setMotoTargetPose(moto_one_pose,0,0,0,0,0);

}
void BaseRun::setMotoTargetPose(uint16_t moto_one, uint16_t moto_two, uint16_t moto_thr, uint16_t moto_fou, uint16_t moto_fiv, uint16_t moto_six)
{
    uint8_t BaseDataBuf[16] = {0};

	BaseDataBuf[0] = 0xAA;
	BaseDataBuf[1] = 0x00;
	BaseDataBuf[2] = 0x00;
    BaseDataBuf[3] = moto_one>>8;
    BaseDataBuf[4] = moto_one;
	BaseDataBuf[5] = moto_two >>8;
    BaseDataBuf[6] = moto_two;
	BaseDataBuf[7] = moto_thr >>8;
	BaseDataBuf[8] = moto_thr;
    BaseDataBuf[9] = moto_fou >>8;
	BaseDataBuf[10] = moto_fou;
	BaseDataBuf[11] = moto_fiv >>8;
    BaseDataBuf[12] = moto_fiv;
    BaseDataBuf[13] = moto_six >>8;
	BaseDataBuf[14] = moto_six;
    BaseDataBuf[15] = 0xBB ;

    try
    {
        serial_.write(BaseDataBuf, sizeof(BaseDataBuf)); 
    }

    catch (serial::IOException &e)
    {
        RCLCPP_ERROR(this->get_logger(), "setMotoTargetSpeed failed through serial port"); 
    }
}
void BaseRun::readSerialData()
{
    while (rclcpp::ok()) 
    {
        // serial_.read(&rx_data[0],9);
        // printf("Frame raw data: %02x %02x %02x %02x %02x %02x %02x %02x %02x \n", 
        //                 rx_data[0], rx_data[1], rx_data[2], rx_data[3], rx_data[4], rx_data[5], 
        //                 rx_data[6], rx_data[7], rx_data[8]);
    }

}
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<BaseRun>("servios_serial_driver");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}