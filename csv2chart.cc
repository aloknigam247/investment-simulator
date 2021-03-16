#include <iostream>
#include <string>
#include <fstream>
#include<boost/tokenizer.hpp>


int main(int argc, char *argv[]) {
    if(argc < 2)
        return 0;

    std::cout << "reading: " << argv[1] << '\n';
    std::ifstream csvfile(argv[1]);
    std::ofstream htmlout("test.html");

    htmlout << R"snip(
<html>
    <head>
        <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
        <script type="text/javascript">
            google.charts.load('current', {'packages':['corechart']});
            google.charts.setOnLoadCallback(drawChart);

            function drawChart() {
                            var data = google.visualization.arrayToDataTable([
)snip";

    std::string line;
    bool firstCol = true, firstRow = true;
    boost::char_separator<char> sep{","};
    while(std::getline(csvfile, line)) {
        boost::tokenizer<boost::char_separator<char>> tok(line, sep);
        if(firstRow)
            htmlout << "                                            [";
        else
            htmlout << ",\n                                            [";
        firstCol = true;
        for (const auto &t : tok) {
            if(firstCol) {
                htmlout << "'" << t << "'";
            }
            else {
                if(firstRow)
                    htmlout << ",  '" << t << "'";
                else
                    htmlout << ",  " << t;
            }
            firstCol = false;
        }
        htmlout << "]";
        firstRow = false;
    }
    htmlout << "\n";
    htmlout << R"snip(
                                        ]);

                            var options = {
                                            title: 'TEST',
                                            curveType: 'function',
                                            legend: { position: 'bottom' }
                                        };

                            var chart = new google.visualization.LineChart(document.getElementById('curve_chart'));

                            chart.draw(data, options);
                        }
        </script>
    </head>
    <body>
        <div id="curve_chart" style="width: 900px; height: 500px"></div>
    </body>
</html>
)snip";
    return 0;
}
