#ifndef TBAI_CORE_INCLUDE_TBAI_CORE_CENTRALCONTROLLER_HPP_
#define TBAI_CORE_INCLUDE_TBAI_CORE_CENTRALCONTROLLER_HPP_

#include <memory>
#include <string>
#include <vector>

#include "tbai_core/Controller.hpp"
#include "tbai_core/StateSubscriber.hpp"
#include "tbai_core/Types.hpp"
#include <std_msgs/String.h>

namespace tbai {
namespace core {

class CentralController {
   public:
    /**
     * @brief Construct a new Central Controller object
     *
     * @param nh : ROS node handle
     * @param stateTopic : topic to subscribe to for state messages
     * @param commandTopic : topic to publish command messages to
     * @param changeControllerTopic : topic to subscribe to for changing controller
     */
    CentralController(ros::NodeHandle &nh, const std::string &stateTopic, const std::string &commandTopic,
                      const std::string &changeControllerTopic);  // NOLINT

    /**
     * @brief Start main control loop
     *
     */
    void start();

    /**
     * @brief Add controller to central controller
     *
     * @param controller : controller to add
     * @param makeActive : whether to make this controller active
     */
    void addController(std::unique_ptr<Controller> controller, bool makeActive = false);

    /**
     * @brief Get state subscriber pointer
     *
     * @return std::shared_ptr<StateSubscriber> : state subscriber pointer
     */
    std::shared_ptr<StateSubscriber> getStateSubscriberPtr();

    /**
     * @brief Get current time in seconds
     *
     * @return scalar_t : current time in seconds
     */
    inline scalar_t getCurrentTime() const { return (ros::Time::now() - initTime_).toSec(); }

   private:
    /** Perform controller step */
    void step(scalar_t currentTime, scalar_t dt);

    /** Perform visualization step */
    inline void visualize() { activeController_->visualize(); }

    /** Callback for changing controller */
    void changeControllerCallback(const std_msgs::String::ConstPtr &msg);

    /** Controllers */
    std::vector<std::unique_ptr<Controller>> controllers_;

    /** Currently used controller */
    Controller *activeController_;

    /** State subscriber */
    std::shared_ptr<StateSubscriber> stateSubscriberPtr_;

    /** ROS stuff */
    ros::Rate loopRate_;
    ros::Time initTime_;
    ros::Publisher commandPublisher_;
    ros::Subscriber changeControllerSubscriber_;
};

}  // namespace core
}  // namespace tbai

#endif  // TBAI_CORE_INCLUDE_TBAI_CORE_CENTRALCONTROLLER_HPP_
