#ifndef DWL_RVIZ_PLUGIN__WHOLE_BODY_STATE_DISPLAY__H
#define DWL_RVIZ_PLUGIN__WHOLE_BODY_STATE_DISPLAY__H

#ifndef Q_MOC_RUN
#include <boost/circular_buffer.hpp>
#endif

#include <rviz/message_filter_display.h>
#include <dwl_rviz_plugin/PointVisual.h>
#include <dwl_rviz_plugin/ArrowVisual.h>
#include <dwl_rviz_plugin/PolygonVisual.h>
#include <dwl_msgs/WholeBodyState.h>
#include <dwl/model/WholeBodyDynamics.h>


namespace Ogre
{
class SceneNode;
}

namespace rviz
{
class EnumProperty;
class ColorProperty;
class FloatProperty;
class IntProperty;
}

namespace dwl_rviz_plugin
{

/**
 * @class WholeBodyStateDisplay
 * @brief Displays a dwl_msgs::WholeBodyState message
 */
class WholeBodyStateDisplay: public rviz::MessageFilterDisplay<dwl_msgs::WholeBodyState>
{
	Q_OBJECT
	public:
		/** @brief Constructor function */
		WholeBodyStateDisplay();

		/** @brief Destructor function */
		~WholeBodyStateDisplay();

		/** @brief Clear the robot model */
		void clear();

		/** @brief Overrides of public virtual functions from the Display class */
		void onInitialize();
		void onEnable();
		void onDisable();
		void fixedFrameChanged();

		/** @brief Clear the visuals by deleting their objects */
		void reset();

		/** @brief Loads a URDF from the ros-param named by our
		 * "Robot Description" property, iterates through the links, and
		 * loads any necessary models. */
		void load();

		/**
		 * @brief Function to handle an incoming ROS message
		 * This is our callback to handle an incoming message
		 * @param const dwl_msgs::WholeBodyState::ConstPtr& Whole-body state msg
		 */
		void processMessage(const dwl_msgs::WholeBodyState::ConstPtr& msg);


	private Q_SLOTS:
		/** @brief Helper function to apply color and alpha to all visuals.
		 * Set the current color and alpha values for each visual */
		void updateRobotModel();
		void updateCoMStyle();
		void updateCoMColorAndAlpha();
		void updateCoMArrowGeometry();
		void updateCoPColorAndAlpha();
		void updateCMPColorAndAlpha();
		void updateICPColorAndAlpha();
		void updateGRFColorAndAlpha();
		void updateGRFArrowGeometry();
		void updateSupportLineColorAndAlpha();
		void updateSupportMeshColorAndAlpha();


	private:
		void processWholeBodyState();

		/** @brief Whole-body state message */
		dwl_msgs::WholeBodyState::ConstPtr msg_;
		bool is_info_;

		/** @brief Robot URDF model */
		std::string robot_model_;
		bool initialized_model_;

		/** @brief Properties to show on side panel */
		rviz::Property* com_category_;
		rviz::Property* cop_category_;
		rviz::Property* cmp_category_;
		rviz::Property* icp_category_;
		rviz::Property* grf_category_;
		rviz::Property* support_category_;

		/** @brief Object for visualization of the data */
		boost::shared_ptr<PointVisual> com_visual_;
		boost::shared_ptr<ArrowVisual> comd_visual_;
		boost::shared_ptr<PointVisual> cop_visual_;
		boost::shared_ptr<PointVisual> cmp_visual_;
		boost::shared_ptr<PointVisual> icp_visual_;
		std::vector<boost::shared_ptr<ArrowVisual> > grf_visual_;
		boost::shared_ptr<PolygonVisual> support_visual_;

		/** @brief Property objects for user-editable properties */
		rviz::StringProperty* robot_model_property_;
		rviz::EnumProperty* com_style_property_;
		rviz::ColorProperty* com_color_property_;
		rviz::FloatProperty* com_alpha_property_;
		rviz::FloatProperty* com_radius_property_;
		rviz::FloatProperty* com_head_radius_property_;
		rviz::FloatProperty* com_head_length_property_;
		rviz::FloatProperty* com_shaft_radius_property_;
		rviz::FloatProperty* com_shaft_length_property_;

		rviz::ColorProperty* cop_color_property_;
		rviz::FloatProperty* cop_alpha_property_;
		rviz::FloatProperty* cop_radius_property_;

		rviz::ColorProperty* cmp_color_property_;
		rviz::FloatProperty* cmp_alpha_property_;
		rviz::FloatProperty* cmp_radius_property_;

		rviz::ColorProperty* icp_color_property_;
		rviz::FloatProperty* icp_alpha_property_;
		rviz::FloatProperty* icp_radius_property_;

		rviz::ColorProperty* grf_color_property_;
		rviz::FloatProperty* grf_alpha_property_;
		rviz::FloatProperty* grf_head_radius_property_;
		rviz::FloatProperty* grf_head_length_property_;
		rviz::FloatProperty* grf_shaft_radius_property_;
		rviz::FloatProperty* grf_shaft_length_property_;

		rviz::ColorProperty* support_line_color_property_;
		rviz::FloatProperty* support_line_alpha_property_;
		rviz::FloatProperty* support_line_radius_property_;
		rviz::ColorProperty* support_mesh_color_property_;
		rviz::FloatProperty* support_mesh_alpha_property_;
		rviz::FloatProperty* support_force_threshold_property_;

		/** @brief Whole-body dynamics */
		dwl::model::WholeBodyDynamics wdyn_;
		dwl::model::FloatingBaseSystem fbs_;
		dwl::math::FrameTF frame_tf_;

		/** @brief Force threshold for detecting active contacts */
		double force_threshold_;

		/** @brief Weight of the robot */
		double weight_;

		/** @brief CoM style */
		enum CoMStyle {REAL, PROJECTED};
		bool com_real_;
};

} //@namespace dwl_rviz_plugin

#endif
