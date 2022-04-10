#include "Bezier.h"

glm::vec3 lerp(const glm::vec3 p1, const glm::vec3 p2, const float t) {
    return p1 * (1 - t) + p2 * t;
}

glm::vec3 de_casteljau(const double t, const std::vector<glm::vec3> &c_point) {
    std::vector<glm::vec3> beta = c_point;
    int N = (int) beta.size();
    for(int j = 1; j < N; j++){
        for(int k = 0; k < N - j; k++){
            beta[k] = lerp(beta[k], beta[k+1], t);
        }
    }
    return beta[0];
}

void BezierSurface(const int w, const int h, const std::vector<std::vector<glm::vec3>> &c_point_grid, std::vector<glm::vec3> &vertices, std::vector<unsigned int> &indices, std::vector<glm::vec2> &TexCoords) {

    std::vector<glm::vec3> b_j;
    float u_r, v_r;
    for(int u = 0; u < w; u++) {
            u_r = static_cast<float>(u) / static_cast<float> (w-1);
            for(auto &i : c_point_grid) {
                b_j.emplace_back(de_casteljau(u_r, i));
            }
            for(int v = 0; v < h; v++) {
                v_r = static_cast<float>(v) / static_cast<float> (h-1);
                vertices.emplace_back(de_casteljau(v_r, b_j));
                TexCoords.emplace_back(glm::vec2(u_r,v_r));
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

void BezierCurve_SegLenght(const float segmentLenght, const float epsilon, const std::vector<glm::vec3> &c_point, std::vector<glm::vec3> &vertices, std::vector<unsigned int> &indices) {
        int index = 0;
        double a = 0.0f;
        double b, m, im;
        m = 0.f;
        glm::vec3 p1, p2;
        p1 = de_casteljau(a, c_point);
        vertices.emplace_back(p1);
        while(glm::distance(p1,c_point.back()) > segmentLenght + epsilon){
            b = 1.0f;
            m = (a+b) / 2.f;
            p2 = de_casteljau(m, c_point);
            im = glm::distance(p1,p2) - segmentLenght;
            while( (im > epsilon or im < -epsilon)){
                if(im > 0) {
                    b = m;
                }
                else {
                    a = m;
                }
                m = (a+b) / 2.f;
                p2 = de_casteljau(m, c_point);
                im = glm::distance(p1,p2) - segmentLenght;
            }
            //std::cout << glm::distance(p1,p2) << std::endl;
            vertices.emplace_back(p2);
            indices.emplace_back(index);
            indices.emplace_back(++index);
            p1 = p2;
            a = m;
        }
        if(m != 1.0f){
            vertices.emplace_back(de_casteljau(1.0f, c_point));
            indices.emplace_back(index);
            indices.emplace_back(++index);
        }
}