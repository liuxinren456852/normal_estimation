#include <vector>
#include <flann/flann.hpp>

#include <fstream>
#include <math.h>
#include <algorithm>
#include <utility>
#include <vector>
#include "/usr/local/include/Eigen/Core"
#include "/usr/local/include/Eigen/Dense"
#include "/usr/local/include/Eigen/Eigen"
#include "/usr/local/include/Eigen/Eigenvalues"

using namespace std;

const float lim_error = 1e-5;       // to stop optimize when not moving
const float lim_diff = 1e-7;        // to stop optimize when not moving
const float thresh_weigh = 0.7;     // weigh threshold value for neighbors when moving point with mean projection of neighbors
const float mu_max = 1.0;           // mu when starting optimize for the first time
const float epsilon = 1e-10;        // small value for initializations of comparisons
const int itr_min = 50;           //
const float coeff_sigma = 3;        // sigma for distance weigh = coeff_sigma*farthestePoint
const float theta_min = 0.00001;    // because theta can not be 0 for phi to make sense
const float init2_accuracy = 50;    // number of vectors tested (maybe decrease to gain time)
const float N_hist = 10;            // number of bins used to find the 2nd initialization
const float itr_opti_pos_plan = 30; // number of iterations to optimize position of point in plane
const int itr_per_mu = 2;

class CApp{
public:    
    int Read(const char* filepath);
    void setRef (int ref);
    void setPoint(Eigen::Vector3f point);
    Eigen::Vector3f getPoint ();
    int get_N_neigh();
    void ComputeDist();
    void SearchFLANNTree(flann::Index<flann::L2<float>>* index,
                                Eigen::Vector3f& input,
                                std::vector<int>& indices,
                                std::vector<float>& dists,
                                int nn);
    void selectNeighbors(int neigh_number);
    void setNormal(Eigen::Vector3f norm);
    void getError(std::vector<float>* error);
    void getErrorNormalized(std::vector<float>* error);
    Eigen::Vector3f getNormal();
    std::vector<Eigen::Vector3f> getNeighborhood();
    float getMoy();
    void getImpact(int *impact, float *sum);
    void pca(Eigen::Vector3f &dir0, Eigen::Vector3f &dir1, Eigen::Vector3f &dir2);
    void Optimize(float div_fact, float lim_mu, double* mu_init);
    void OptimizePos(int it);
    void OptimizePos1(float div_fact, float lim_mu, double* mu_init);
    void writeNormal(const char* filepath);
    void writeNeighbors(std::string filepath);
    void writeErrors(std::string filepath);
    void addSymmetricDist();
    void buildTree();
    Eigen::Vector3f getVecMoy();
    void initNormal();
    void select_normal(int* impact, int impact1, float sum_error, float sum_error1, Eigen::Vector3f &normal_first2, Eigen::Vector3f &normal_second2, Eigen::Vector3f& point_first, Eigen::Vector3f& point_second);
    void getEdgeDirection(int it);
    void setTree(flann::Index<flann::L2<float>> *t);
    void setPc(std::vector<Eigen::Vector3f> *pc);


private:
	// containers
    std::vector<Eigen::Vector3f> *pointcloud_;
    flann::Index<flann::L2<float>>* tree_;
    std::vector<Eigen::Vector3f> neighborhood_;
    std::vector<float> poids_;
    std::vector<Eigen::Vector3f> dist_;
    int ref_;
    Eigen::Vector3f pt;
    Eigen::Vector3f normal;
    float theta;
    float phi;
    std::vector<float> error_;
    std::vector<float> diff_poids_;
    std::vector<float> diff_error_;
    Eigen::Vector3f moy_;
    void ComputeWeighs(double mu);
    void ComputeWeighs_proj(double mu);
    void actuNormal( float phi_new, float theta_new);
};
