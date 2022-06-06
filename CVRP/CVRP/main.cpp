#include <cstdint>
#include <vector>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

#include "google/protobuf/duration.pb.h"
#include "ortools/constraint_solver/routing.h"
#include "ortools/constraint_solver/routing_enums.pb.h"
#include "ortools/constraint_solver/routing_index_manager.h"
#include "ortools/constraint_solver/routing_parameters.h"

struct Point 
{
    double x;
    double y;
};

double dist(Point p1, Point p2) 
{
    return sqrt(pow((p1.x - p2.x),2) + pow((p1.y - p2.y),2));
}

void readInput(std::vector<std::vector<double>>& matrix, int m, std::vector<Point>& points) 
{
    int p, q;
    for (p = 0; p < m; p++) 
    {
        for (q = 0; q < m; q++) 
        {
            if (p == q) 
            {
                matrix[p][q] = 0;
            } else 
            {
                matrix[p][q] = dist(points[p], points[q]);
            }
        }
    }
}

namespace operations_research 
{
struct DataModel
{
    std::vector<std::vector<double>> distance_matrix;
    std::vector<int64_t> demands;
    std::vector<int64_t> vehicle_capacities;
    int64_t num_vehicles = 0;
    RoutingIndexManager::NodeIndex depot{0};
};

void PrintSolution(const DataModel& data, const RoutingIndexManager& manager,
                   const RoutingModel& routing, const Assignment& solution)
{
  int64_t final_distance{0};
  int64_t final_load{0};
  for (int vehicle_id = 0; vehicle_id < data.num_vehicles; ++vehicle_id)
  {
    int64_t id = routing.Start(vehicle_id);
   int64_t run_distance{0};
    int64_t run_load{0};
    std::stringstream route;
    while (routing.IsEnd(id) == false)
    {
      int64_t node_id = manager.IndexToNode(id).value();
      run_load += data.demands[node_id];
      int64_t previous_id = id;
      id = solution.Value(routing.NextVar(id));
      run_distance += routing.GetArcCostForVehicle(previous_id, id,
      int64_t{vehicle_id});
    }
    final_distance += run_distance;
    final_load += run_load;
  }
  std::cout << final_distance << std::endl;
}
void VrpCapacity(DataModel init_data)
{
  DataModel data = init_data;
  RoutingIndexManager manager(data.distance_matrix.size(), data.num_vehicles,
                              data.depot);
  RoutingModel routing(manager);
  const int transit_callback_index = routing.RegisterTransitCallback(
      [&data, &manager](int64_t from_index, int64_t to_index) -> int64_t  
      {
        int from_node = manager.IndexToNode(from_index).value();
        int to_node = manager.IndexToNode(to_index).value();
        return data.distance_matrix[from_node][to_node];
      });
  routing.SetArcCostEvaluatorOfAllVehicles(transit_callback_index);
  const int demand_callback_index = routing.RegisterUnaryTransitCallback(
      [&data, &manager](int64_t from_index) -> int64_t 
      {
        int from_node = manager.IndexToNode(from_index).value();
        return data.demands[from_node];
      });
  routing.AddDimensionWithVehicleCapacity(
      demand_callback_index,   
      int64_t{0},               
      data.vehicle_capacities, 
      true,                     
      "Capacity");
  RoutingSearchParameters search_parameters = DefaultRoutingSearchParameters();
  search_parameters.set_first_solution_strategy(
      FirstSolutionStrategy::PATH_CHEAPEST_ARC);
  search_parameters.set_local_search_metaheuristic(
      LocalSearchMetaheuristic::GUIDED_LOCAL_SEARCH);
  search_parameters.mutable_time_limit()->set_seconds(300);
  const Assignment* solution = routing.SolveWithParameters(search_parameters);
  PrintSolution(data, manager, routing, *solution);
}
}

int main(int argc, char** argv)
{
    std::string track = "/Users/annalarina/vrp_hard_test";
           auto u = fs::directory_iterator(track);
           std::vector<fs::path> array_track;
           copy_if(fs::begin(u), fs::end(u), std::back_inserter(array_track),
               [](const auto& entry) 
               {
                   return fs::is_regular_file(entry);
           });
    for (auto& t : array_track)
    {
        std::ifstream fin;
        fin.open(t.string());
        std::cout << t.string() << std::endl;
        int64_t m, vehicles_num, capacities_vehicle;
        fin >> m >> vehicles_num >> capacities_vehicle;
        std::vector<int64_t> buffer(vehicles_num, capacities_vehicle);
        operations_research::DataModel data;
        data.vehicle_capacities = buffer;
        data.num_vehicles = nvehicles_num;
        std::vector<Point> points(m);
        std::vector<int64_t> buf(m);
        int p;
        for (p = 0; p < m; p++) 
        {
            int64_t d;
            Point t;
            fin >> d >> t.x >> t.y;
            points[p] = t;
            buf[p] = d;
        }
        std::vector<std::vector<double> > array(m, std::vector<double>(m));
        readInput(array, m, points);
        data.demands = buf;
        data.distance_matrix = array;
        operations_research::VrpCapacity(data);
    }
    return EXIT_SUCCESS;
}
