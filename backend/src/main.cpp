#include <crow.h>
#include <ortools/linear_solver/linear_solver.h>

#include <string>

using namespace operations_research;

void add_cors_headers(crow::response& res) {
	res.add_header("Access-Control-Allow-Origin", "*");
	res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
	res.add_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
}

std::string solve_optimization() {
    MPSolver solver("SimpleLP", MPSolver::GLOP_LINEAR_PROGRAMMING);

    // 変数を定義
    MPVariable *const x = solver.MakeNumVar(0.0, 3.0, "x");
    MPVariable *const y = solver.MakeNumVar(0.0, 2.0, "y");

    // 目的関数: Maximize x + y
    MPObjective *const objective = solver.MutableObjective();
    objective->SetCoefficient(x, 1);
    objective->SetCoefficient(y, 1);
    objective->SetMaximization();

    // 制約: x + 2y <= 3
    MPConstraint* const constraint = solver.MakeRowConstraint(0.0, 3.0);
    constraint->SetCoefficient(x, 1);  // x の係数を設定
    constraint->SetCoefficient(y, 2); // y の係数を設定

    // 解を求める
    if (solver.Solve() == MPSolver::OPTIMAL) {
        return "Solution: x = " + std::to_string(x->solution_value()) +
               ", y = " + std::to_string(y->solution_value());
    } else {
        return "No solution found.";
    }
}

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
				crow::response res;
				add_cors_headers(res);
				res.write(solve_optimization());
				return res;
    });

    app.port(18080).multithreaded().run();
}

