// #include <pybind11
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
