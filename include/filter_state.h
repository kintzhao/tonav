//
// Created by Tomas Krejci on 5/17/16.
//

#ifndef TONAV_FILTER_STATE_H
#define TONAV_FILTER_STATE_H

#include <iostream>
#include <Eigen/Dense>
#include <list>

#include "camera_pose.h"

class FilterState {
public:
    using StateType = Eigen::Matrix<double, 57, 1>;

    Eigen::Block<StateType, 4, 1> getRotationBlock();
    Eigen::Quaterniond getRotationQuaternion();
    void setRotationQuaternion(const Eigen::Quaterniond& quat);
    Eigen::Block<StateType, 3, 1> getPositionBlock();
    Eigen::Block<StateType, 3, 1> getVelocityBlock();
    Eigen::Block<StateType, 3, 1> getAccelerometerBiasBlock();
    Eigen::Block<StateType, 3, 1> getGyroscopeBiasBlock();

    Eigen::Block<StateType, 9, 1> getGyroscopeShapeVectorizedBlock();
    Eigen::Block<StateType, 9, 1> getGSensitivityVectorizedBlock();
    Eigen::Block<StateType, 9, 1> getAccelerometerShapeVectorizedBlock();

    Eigen::Block<StateType, 3, 1> getCameraToBodyOffsetBlock();

    double& getFocalLengthXRef();
    double& getFocalLengthYRef();
    double& getOpticalCenterXRef();
    double& getOpticalCenterYRef();

    Eigen::Block<StateType, 3, 1> getRadialDistortionParametersBlock();
    Eigen::Block<StateType, 2, 1> getTangentialDistortionParametersBlock();

    double& getCameraDelayTimeRef();
    double& getCameraReadoutTimeRef();

    Eigen::Block<Eigen::Vector3d, 3, 1> getRotationEstimateBlock();
    Eigen::Block<Eigen::Vector3d, 3, 1> getAccelerationEstimateBlock();

    Eigen::Quaterniond getRotationToThisFrame();
    void setRotationToThisFrame(const Eigen::Quaterniond& quat);

    std::ostream& uglyPrint(std::ostream& out) const;

    FilterState deriveNewStateForImuPropagation() const;

    void appendCameraPose(const CameraPose& camera_pose);

private:
    StateType state_;
    Eigen::Quaterniond rotation_to_this_frame_;
    Eigen::Vector3d rotation_estimate_;
    Eigen::Vector3d acceleration_estimate_;

    std::list<CameraPose> poses_;
};

std::ostream& operator<< (std::ostream& out, FilterState& state);

#endif //TONAV_FILTER_STATE_H
