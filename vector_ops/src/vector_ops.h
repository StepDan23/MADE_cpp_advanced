#pragma once
#include <vector>
#include <iostream>
# include <cmath>

using namespace std;


namespace task {

    vector<double> operator+(vector<double> vec, vector<double> vec_1) {
        for (size_t i = 0; i < vec.size(); ++i)
            vec[i] += vec_1[i];
        return vec;
    }

    vector<double> operator-(vector<double> vec, vector<double> vec_1) {
        for (size_t i = 0; i < vec.size(); ++i)
            vec[i] -= vec_1[i];
        return vec;
    }

    vector<double> operator+(vector<double> vec) {
        return vec;
    }

    vector<double> operator-(vector<double> vec) {
        for (size_t i = 0; i < vec.size(); ++i)
            vec[i] = -vec[i];
        return vec;
    }

    double operator*(vector<double> vec, vector<double> vec_1) {
        double result = 0;

        for (size_t i = 0; i < vec.size(); ++i)
            result += vec[i] * vec_1[i];
        return result;
    }

    vector<double> operator%(vector<double> vec, vector<double> vec_1) {
        vector<double> new_vec(vec.size());

        new_vec[0] = vec[2] * vec_1[1] - vec[1] * vec_1[2];
        new_vec[1] = vec[0] * vec_1[2] - vec[2] * vec_1[0];
        new_vec[2] = vec[1] * vec_1[0] - vec[0] * vec_1[1];

        return new_vec;
    }

    bool operator||(vector<double> vec, vector<double> vec_1)  {
        const double EPS = 1e-7;
        double cos_fi = vec * vec_1 / sqrt((vec * vec) * (vec_1 * vec_1));

        if (1.0 - (abs(cos_fi)) > EPS)
            return false;

        return true;
    }

    bool operator&&(vector<double> vec, vector<double> vec_1)  {
        const double EPS = 1e-7;
        double ratio = vec[0] / vec_1[0];

        if (ratio < 0)
            return false;

        for (size_t i = 0; i < vec.size(); ++i)
            if (abs(ratio - vec[i] / vec_1[i]) > EPS)
                return false;

        return true;
    }

    vector<int> operator|(vector<int> vec, vector<int> vec_1) {
        for (size_t i = 0; i < vec.size(); ++i)
            vec[i] |= vec_1[i];

        return vec;
    }

    vector<int> operator&(vector<int> vec, vector<int> vec_1) {
        for (size_t i = 0; i < vec.size(); ++i)
            vec[i] &= vec_1[i];

        return vec;
    }

    ostream &operator<<(ostream &out, vector<double> vec) {
        for (auto val: vec)
            out << val << ' ';
        out << endl;

        return out;
    }

    istream &operator>>(istream &in, vector<double> &vec) {
        int vec_size;

        in >> vec_size;
        vec.resize(vec_size);

        for (size_t i = 0; i < vec_size; ++i)
            in >> vec[i];

        return in;
    }

    void reverse(vector<double> &vec){
        for (size_t i = 0; i < vec.size() / 2; ++i)
            swap(vec[i], vec[vec.size() - 1 - i]);
    }
}
