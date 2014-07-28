#ifndef _MATRIXOPS_H
#define _MATRIXOPS_H

#include "common.h"
#include <string>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtx/orthonormalize.hpp>

// extra Matrix functions that aren't easily provided by glm

namespace Matrix {

    inline float index(glm::mat4& m, unsigned int idx) {
        float* f = glm::value_ptr(m);
        return f[idx];
    }

    inline void reset_orientation(glm::mat4& m) {
        float* f = glm::value_ptr(m);
        f[1]=f[2]=f[4]=f[5]=f[8]=f[9]=0.0f;
        f[0]=f[5]=f[10]=1.0f;
    }
    inline glm::mat3 orientation(const glm::mat4& m) {
        glm::mat3 r;
        float* rf = glm::value_ptr(r);
        const float* mf = glm::value_ptr(m);
        for(unsigned i=0;i<=2;++i)
            rf[i] = mf[i];
        for(unsigned i=4;i<=6;++i)
            rf[i-1] = mf[i];
        for(unsigned i=8;i<=10;++i)
            rf[i-2] = mf[i];
        return r;
    }
    inline glm::vec3 translation(const glm::mat4& m){
        const float* f = glm::value_ptr(m);
        return glm::vec3(f[12], f[13], f[14]);
    }
    inline void wScale(glm::mat4& m, float v = 1.0f) {
        float* f = glm::value_ptr(m);
        f[15] = v;
    }
    inline std::string to_string(const glm::mat4& m) {
        const float* f = glm::value_ptr(m);
        std::ostringstream ss;
        std::string s;
        for(int i=0; i<16; i++) {
            ss.str("");
            ss << f[i];
            s += (s.empty()?"":" ") + ss.str();
        }
        return s;
    }
    //inline glm::vec3 check(const glm::mat4& m) {
    //    const float* f = glm::value_ptr(m);
    //    assert(floatcmp(f[3],0.0f));
    //    assert(floatcmp(f[7],0.0f));
    //    assert(floatcmp(f[11],0.0f));
    //    assert(floatcmp(f[15],1.0f));
    //}
    inline void translation(glm::mat4& m, const glm::vec3& t){
        float* f = glm::value_ptr(m);
        f[12] = t[0];
        f[13] = t[1];
        f[14] = t[2];
    }
    inline void translate(glm::mat4& m, const glm::vec3& t) {
        float* f = glm::value_ptr(m);
        f[12] += t[0];
        f[13] += t[1];
        f[14] += t[2];
    }
    inline void reset_translation(glm::mat4& m) {
        float* f = glm::value_ptr(m);
        f[12]=f[13]=f[14]=0.0f;
    }
    inline void scale(glm::mat4& m, float v) {
        float* f = glm::value_ptr(m);
        m *= v;
        //f[0]*=v;
        //f[5]*=v;
        //f[10]*=v;
    }
    inline void rescale(glm::mat4& m, float v = 1.0f) {
        float* f = glm::value_ptr(m);
        f[0]=f[5]=f[10]=v;
        f[15]=1.0f;
    }
    inline void scale(glm::mat4& m, glm::vec3 v) {
        float* f = glm::value_ptr(m);
        m *= glm::vec4(v, 1.0f);
        //f[0]*=v[0];
        //f[5]*=v[1];
        //f[10]*=v[2];
    }
    inline void rescale(glm::mat4& m, glm::vec3 v = glm::vec3(1.0f)) {
        float* f = glm::value_ptr(m);
        f[0]=v[0];
        f[5]=v[1];
        f[10]=v[2];
        f[15]=1.0f;
    }
    // assuming uniform scale
    inline float uniform_scale(glm::mat4& m) {
        float* f = glm::value_ptr(m);
        return f[0];
    }
    //inline float average_scale(glm::mat4& m) {
    //    float* f = glm::value_ptr(m);
    //    return (f[0] + f[5] + f[10]) / 3.0f;
    //}

    inline glm::vec3 up(const glm::mat4& m) {
        const float* f = glm::value_ptr(m);
        return glm::vec3(f[4], f[5], f[6]);
    }
    inline glm::vec3 heading(const glm::mat4& m)
    {
        const float* f = glm::value_ptr(m);
        return -glm::vec3(f[8], f[9], f[10]);
    }
    
    // remember to normalize after computing these
    inline glm::vec3 upXZ(const glm::mat4& m)
    {
        glm::vec3 r = up(m);
        r.y = 0.0f;
        return glm::normalize(r);
    }
    inline glm::vec3 headingXZ(const glm::mat4& m)
    {
        glm::vec3 r = heading(m);
        r.y = 0.0f;
        return glm::normalize(r);
    }
    
    inline bool is_identity(const glm::mat4& m)
    {
        // glm takes care of floatcmp and epsilon value
        return m == glm::mat4(1.0f);
    }
    
    inline bool is_zero(const glm::mat4& m)
    {
        // glm takes care of floatcmp and epsilon value
        return m == glm::mat4(0.0f);
    }
    
    inline glm::vec3 mult(const glm::vec3& v, const glm::mat4& m)
    {
        auto r = glm::vec4(v, 1.0f) * m;
        return glm::vec3(r.x, r.y, r.z);
    }
    inline glm::vec3 mult(const glm::mat4& m, const glm::vec3& v)
    {
        auto r = m * glm::vec4(v, 1.0f);
        return glm::vec3(r.x,r.y,r.z);
    }
    
    inline glm::mat4 from_array(const float* f)
    {
        glm::mat4 m;
        float* m_array = glm::value_ptr(m);
        for(int i=0;i<16;i++)
            m_array[i] = f[i];
        return m;
    }

    inline float* ptr(glm::mat4& m) {
        return glm::value_ptr(m);
    }
    inline const float* ptr(const glm::mat4& m) {
        return glm::value_ptr(m);
    }
}

#endif

