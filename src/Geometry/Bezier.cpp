#include <iostream>
#include "Bezier.h"

glm::vec3 lerp(const glm::vec3 p1, const glm::vec3 p2, const float t) {
    return p1 * (1 - t) + p2 * t;
}

glm::vec3 de_casteljau(const float t, const std::vector<glm::vec3> &c_point) {
    std::vector<glm::vec3> beta = c_point;
    int N = (int) beta.size();
    for(int j = 1; j < N; j++){
        for(int k = 0; k < N - j; k++){
            beta[k] = lerp(beta[k], beta[k+1], t);
        }
    }
    return beta[0];
}

void BezierSurface(const int w, const int h, const std::vector<std::vector<glm::vec3>> &c_point_grid, std::vector<glm::vec3> &vertices, std::vector<unsigned int> &indices) {

    std::vector<glm::vec3> b_j;
    for(int u = 0; u < w; u++) {
            for(auto &i : c_point_grid) {
                b_j.emplace_back(de_casteljau(static_cast<float>(u) / static_cast<float> (w-1), i));
            }
            for(int v = 0; v < h; v++) {
                    vertices.emplace_back(de_casteljau(static_cast<float>(v) / static_cast<float> (h-1), b_j));
            }
            b_j.clear();
    }
    for(int i = 0; i < w-1; i++){
        for(int j = 0; j < h-1; j++){
            indices.emplace_back(i*h+j);
            indices.emplace_back(i*h+j+1);
            indices.emplace_back((i+1)*h+j+1);
            indices.emplace_back(i*h+j);
            indices.emplace_back((i+1)*h+j+1);
            indices.emplace_back((i+1)*h+j);
        }
    }

}

void BezierCurve_SegCount(const int nb_segment, const std::vector<glm::vec3> &c_point, std::vector<glm::vec3> &vertices, std::vector<unsigned int> &indices) {

    int seg_count = 0;

    for(int u = 0; u < nb_segment; u++) {
        vertices.emplace_back(de_casteljau( static_cast<float>(u) / static_cast<float> (nb_segment-1), c_point));
        if(seg_count == 0) {
            indices.emplace_back(seg_count++);
        }
        else{
            indices.emplace_back(seg_count);
            indices.emplace_back(seg_count++);
        }
    }

    assert(seg_count == nb_segment);
}

void BezierCurve_SegLenght(const float segmentLenght, const std::vector<glm::vec3> &c_point, std::vector<glm::vec3> &vertices, std::vector<unsigned int> &indices) {
    double step = 1.0f/(double) segmentLenght;
    int index = 0;
    for(double t = 0.0; t < 1.0+step; t+=step) {
        vertices.emplace_back(de_casteljau(t, c_point));
        if(index > 0) {
            indices.emplace_back(index-1);
            indices.emplace_back(index);
        }
        index++;
    }
}