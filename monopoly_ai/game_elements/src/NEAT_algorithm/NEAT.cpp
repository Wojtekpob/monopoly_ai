/*
 * This file defines the NEATAI class, which integrates a Python-based AI using the NEAT algorithm into a C++ application.
 * The class uses pybind11 to interface with Python, allowing it to train the AI and get actions based on the game state.
 * The NEATAI class includes methods for training the AI with game states and retrieving an action based on the current game state.
 * It also manages the Python interpreter's lifecycle by initializing and finalizing it within the constructor and destructor.
 *
 * Author: Mikołaj Sendybył
 */

#include <pybind11/stl.h>
#include <pybind11/embed.h>
#include <vector>
#include <string>
#include <map>

namespace py = pybind11;

class NEATAI {
public:
    NEATAI(const std::string& config_file) : config_file(config_file) {
        py::initialize_interpreter();
        py::module_ monopoly_ai = py::module_::import("monopoly_ai");
        train_ai = monopoly_ai.attr("train_ai");
        get_action = monopoly_ai.attr("get_action");
    }

    ~NEATAI() {
        py::finalize_interpreter();
    }

    void train(const std::vector<std::map<std::string, py::object>>& game_states, int generations) {
        train_ai(config_file, game_states, generations);
    }

    int get_action(double money, int position, const std::vector<int>& properties) {
        py::dict game_state;
        game_state["money"] = money;
        game_state["position"] = position;
        game_state["properties"] = properties;

        return get_action(config_file, game_state).cast<int>();
    }

private:
    std::string config_file;
    py::object train_ai;
    py::object get_action;
};

PYBIND11_MODULE(monopoly_ai_cpp, m) {
    py::class_<NEATAI>(m, "NEATAI")
        .def(py::init<const std::string&>())
        .def("train", &NEATAI::train)
        .def("get_action", &NEATAI::get_action);
}
