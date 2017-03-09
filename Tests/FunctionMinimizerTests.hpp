/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FunctionMinimizerTests.hpp
 * Author: matthewsupernaw
 *
 * Created on March 8, 2017, 2:15 PM
 */

#ifndef FUNCTIONMINIMIZERTESTS_HPP
#define FUNCTIONMINIMIZERTESTS_HPP

#include "../Optimization.hpp"
#include <vector>

namespace atl {
    namespace tests {
        namespace fmin {

            template<typename T>
            struct MinimizerTest {

                bool const IsClose(const T& f1, const T& f2, T figures_tolerance = 3.0) {
                    T res = f1 - f2;
                    res = res * std::pow(10.0, figures_tolerance);
                    return !bool(int(res));
                }

            };

            template<typename T>
            struct Rosenbrock : atl::ObjectiveFunction<T>, MinimizerTest<T> {
                typedef atl::Variable<T> var;
                std::vector<var> x;
                T f_;

                void Initialize() {
                    x.resize(10);
                    T temp = -10.0;
                    for (int i = 0; i < x.size(); i++) {
                        std::stringstream ss;
                        ss << "x_" << i;
                        x[i] = temp += 1.2; //(var(i));
                        x[i].SetName(ss.str());
                        this->RegisterParameter(x[i]);

                    }



                }

                void ObjectiveFunction(var& f) {
                    f = static_cast<T> (0.0);
                    for (int i = 0; i < x.size() - 1; i++) {
                        f += 100.0 * atl::pow(x[i + 1] - atl::pow(x[i], 2.0), 2.0) + atl::pow(x[i] - 1.0, 2.0);
                    }
                    this->f_ = f.GetValue();
                }

                const atl::Variable<T> Evaluate() {
                    atl::Variable<T> f;
                    this->ObjectiveFunction(f);
                    return f;
                }

                bool Check() {
                    if (this->IsClose(this->f_, 1e-5, 3.0)) {
                        return true;
                    } else {
                        return false;
                    }
                }


            };

            template<class T>
            class Schaffer : public atl::ObjectiveFunction<T>, MinimizerTest<T> {
            public:
                typedef atl::Variable<T> var;
                var x;
                var y;
                T f_;

                void Initialize() {
                    x = -0.0324234;
                    x.SetName("x");
                    y = 1.01;
                    y.SetName("y");

                    this->RegisterParameter(x);
                    this->RegisterParameter(y);
                }

                void ObjectiveFunction(var& f) {
                    f = 0.5 + (atl::pow(atl::sin(atl::pow(x, 2.0) - atl::pow(y, 2.0)), 2.0) - 0.5) / atl::pow(1.0 + .001 * (atl::pow(x, 2.0) + atl::pow(y, 2.0)), 2.0);
                    f_ = f.GetValue();
                }

                const atl::Variable<T> Evaluate() {
                    atl::Variable<T> f;
                    this->ObjectiveFunction(f);
                    return f;
                }

                bool Check() {
                    if (this->IsClose(this->f_, 1e-5, 3.0)) {
                        return true;
                    } else {
                        return false;
                    }
                }

            };

            template<class T>
            class McCormick : public atl::ObjectiveFunction<T>, MinimizerTest<T> {
            public:
                typedef atl::Variable<T> var;
                var x;
                var y;
                T f_;

                void Initialize() {
                    x = -1.4;
                    x.SetName("x");
                    y = 2.0;
                    y.SetName("y");

                    this->RegisterParameter(x);
                    this->RegisterParameter(y);
                }

                void ObjectiveFunction(var& f) {
                    f = atl::sin(x + y) + atl::pow(x - y, 2.0) - 1.5 * x + 2.5 * y + 1.0;
                    f_ = f.GetValue();
                }

                bool Check() {
                    if (this->IsClose(x.GetValue(), -0.54719, 3.0) && this->IsClose(y.GetValue(), -1.54719, 3.0)) {
                        return true;
                    } else {
                        return false;
                    }
                }

                const atl::Variable<T> Evaluate() {
                    atl::Variable<T> f;
                    this->ObjectiveFunction(f);
                    return f;
                }

            };

            template<class T>
            class Easom : public atl::ObjectiveFunction<T>, MinimizerTest<T> {
            public:
                typedef atl::Variable<T> var;
                var x;
                var y;
                T f_;

                void Initialize() {
                    x = M_PI - 2.0;
                    x.SetName("x");
                    y = M_PI - 2.0;
                    y.SetName("y");

                    this->RegisterParameter(x);
                    this->RegisterParameter(y);
                }

                void ObjectiveFunction(var& f) {
                    f = -1.0 * atl::cos(x) * atl::cos(y) * atl::exp(-1.0 * (atl::pow(x - M_PI, 2.0) + atl::pow(y - M_PI, 2.0)));
                    f_ = f.GetValue();
                }

                bool Check() {
                    if (this->IsClose(x.GetValue(), M_PI, 3.0) && this->IsClose(y.GetValue(), M_PI, 3.0)) {
                        return true;
                    } else {
                        return false;
                    }
                }

                const atl::Variable<T> Evaluate() {
                    atl::Variable<T> f;
                    this->ObjectiveFunction(f);
                    return f;
                }

            };

            template<class T>
            class Bukin : public atl::ObjectiveFunction<T>, MinimizerTest<T> {
            public:
                typedef atl::Variable<T> var;
                var x;
                var y;
                T f_;

                void Initialize() {
                    x = -15.0;
                    x.SetName("x");
                    y = 2.0;
                    y.SetName("y");
                    this->RegisterParameter(x);
                    this->RegisterParameter(y);
                }

                void ObjectiveFunction(var& f) {
                    f = 100.0 * atl::sqrt(atl::ad_fabs<T>(y - .01 * atl::pow(x, 2.0), 1e-4)) + .01 * atl::ad_fabs<T>(x + 10.0, 1e-4);
                    f_ = f.GetValue();
                }

                bool Check() {
                    if (this->IsClose(x.GetValue(), -10.0) && this->IsClose(y.GetValue(), 1.0)) {
                        return true;
                    } else {
                        return false;
                    }
                }

                const atl::Variable<T> Evaluate() {
                    atl::Variable<T> f;
                    this->ObjectiveFunction(f);
                    return f;
                }


            };

            template<class T>
            class StyblinskiTang : public atl::ObjectiveFunction<T>, MinimizerTest<T> {
            public:
                typedef atl::Variable<T> var;
                std::vector<var> x;

                void Initialize() {
                    x.resize(10);
                    T temp = -5.0;
                    for (int i = 0; i < x.size(); i++) {
                        x[i] = temp += .002; //(var(i));
                        std::stringstream ss;
                        ss<<"x_"<<i;
                        x[i].SetName(ss.str());
                        this->RegisterParameter(x[i]);

                    }



                }

                void ObjectiveFunction(var& f) {
                    f = static_cast<T> (0.0);
                    var sum;
                    for (int i = 0; i < x.size(); i++) {
                        sum += atl::pow(x[i], 4.0) - 16.0 * atl::pow(x[i], 2.0) + 5.0 * x[i];
                    }
                    f = sum / 2.0;
                }

                bool Check() {
                    for (int i = 0; i < x.size(); i++) {
                        if (!this->IsClose(x[i].GetValue(), -2.9035, 3.0)) {
                            return false;
                        }
                    }
                    return true;
                }

                const atl::Variable<T> Evaluate() {
                    atl::Variable<T> f;
                    this->ObjectiveFunction(f);
                    return f;
                }


            };

            void Run() {

                atl::tests::fmin::Rosenbrock<double> rosenbrock;
                rosenbrock.Initialize();
                atl::PortMinimizer<double> lbfgs;
                lbfgs.SetObjectiveFunction(&rosenbrock);
                lbfgs.Run();
                if (rosenbrock.Check()) {
                    std::cout << "Rosenbrock test passed.\n";
                } else {
                    std::cout << "Rosenbrock test failed.\n";
                }

                Schaffer<double> shaffer;
                shaffer.Initialize();
                lbfgs.SetObjectiveFunction(&shaffer);
                lbfgs.Run();
                if (shaffer.Check()) {
                    std::cout << "Shaefer test passed.\n";
                } else {
                    std::cout << "Shaefer test failed.\n";
                }

                atl::tests::fmin::McCormick<double> mccormick;
                mccormick.Initialize();
                lbfgs.SetObjectiveFunction(&mccormick);
                lbfgs.Run();
                if (mccormick.Check()) {
                    std::cout << "McCormick test passed.\n";
                } else {
                    std::cout << "McCormick test failed.\n";
                }


                atl::tests::fmin::Easom<double> easom;
                easom.Initialize();
                lbfgs.SetObjectiveFunction(&easom);
                lbfgs.Run();
                if (easom.Check()) {
                    std::cout << "Easom test passed.\n";
                } else {
                    std::cout << "Easom test failed.\n";
                }

                atl::tests::fmin::Bukin<double> bukin;
                bukin.Initialize();
                lbfgs.SetObjectiveFunction(&bukin);
                lbfgs.Run();
                if (bukin.Check()) {
                    std::cout << "Bukin test passed.\n";
                } else {
                    std::cout << "Bukin test failed.\n";
                }


                atl::tests::fmin::StyblinskiTang<double> styblinski_tang;
                styblinski_tang.Initialize();
                lbfgs.SetObjectiveFunction(&styblinski_tang);
                lbfgs.Run();
                if (styblinski_tang.Check()) {
                    std::cout << "StyblinskiTang test passed.\n";
                } else {
                    std::cout << "StyblinskiTang test failed.\n";
                }

            }



        }
    }
}


#endif /* FUNCTIONMINIMIZERTESTS_HPP */
