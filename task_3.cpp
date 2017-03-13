using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace task_3 {
    class Program {
        static void Main(string[] args) {

            Algorythm alg = new Algorythm();
            alg.getDataFromFile();
            alg.Dejkstra();
            alg.putDataInFile();

        }
    }
}


internal class Graf {

    public bool visited = false;     //
    public bool tmpVisited = false;
    public int begin, end, rebro;
    public int weight = 10000;

    internal Graf(int begin, int end, int rebro) {
        this.begin = begin;
        this.end = end;
        this.rebro = rebro;
    }

}



public class Algorythm {

    int[,] arrCross; //матрица смежности
    int[] datain;    //массив входных данных
    int start = 0;   //начало вепоиска
    int end = 0;     //конец поиска
    int time;        //ресурс, за который будет пройден путь

    List<Graf> graf = new List<Graf>();

    //извлекаем данные из файла
    public void getDataFromFile() {
        try {
            var sr = new StreamReader("input.txt");
            datain = extractData(sr).ToArray();
            inputData(datain);
        }
        catch (IOException e) {
            Console.WriteLine(e.Message);
        }
    }

    //извлекаем данные из файла
    public static IEnumerable<int> extractData(StreamReader sr) {
        string line;
        while ((line = sr.ReadLine()) != null) {
            var items = line.Split(' ');
            foreach (var item in items) {
                yield return Convert.ToInt32(item);
            }
        }
    }


    //заносим данные в программу
    void inputData(int[] data) {

        arrCross = new int[data[0] + 2, data[0]];

        for (int i = 0; i < data[0]; i++) {
            for (int j = 0; j < data[0]; j++) {
                arrCross[i, j] = 100000;
            }
        }

        start = data[data.Length - 2];
        end = data[data.Length - 1];

        for (int i = 2; i < data.Length - 2; i += 3) {
            graf.Add(new Graf(data[i], data[i + 1], data[i + 2]));
        }

        foreach (Graf gr in graf) {
            if (gr.begin == start) {
                gr.weight = 0;
            }
        }

    }


    public void Dejkstra() {

        int count = 0;         //счетчик
        int min = 10000;       //мин значение
        int vertex = start;    //вершина
        int vertextmp = start; //временная вершина
        int vis = start;       // номер посещенной вершины
        int ex = 10000;

        try {
            // пробегаемся по строкам массива
            for (int i = 0; i < datain[0]; i++) {
                // пробегаемся по графам
                foreach (Graf gr in graf) {
                    if (gr.begin == vertex) {

                        // если вес меньше пред, то пишем в массив
                        if (gr.weight + gr.rebro < arrCross[i, gr.end - 1]) {
                            arrCross[i + 1, gr.end - 1] = gr.weight + gr.rebro;
                        }
                        // если нет, то пред значение
                        else {
                            arrCross[i + 1, gr.end - 1] = arrCross[i, gr.end - 1];
                        }

                        // заносим мин вес в соседнюю вершину
                        foreach (Graf gr2 in graf) {
                            if (end == gr.end) {
                                if (ex > gr.weight + gr.rebro) { ex = gr.weight + gr.rebro; }
                            }
                            if (gr2.begin == gr.end) {
                                if (gr.weight + gr.rebro < gr2.weight) {
                                    gr2.weight = gr.weight + gr.rebro;
                                }
                            }
                        }
                    }

                }//end foreach

                min = 10000;
                // ищем вершину с мин ребром
                for (int j = 0; j < datain[0]; j++) {
                    if (min > arrCross[i + 1, j]) {
                        min = arrCross[i + 1, j];
                        vertex = j + 1;
                    }
                }

                // сносим вниз все кроме посещенной вершины
                for (int j = 0; j < datain[0]; j++) {
                    if (j != vertex - 1) {
                        arrCross[i + 2, j] = arrCross[i + 1, j];
                    }
                }
            }
            time = ex;// min time
        }
        catch (Exception) { time = 1000000000; }
    }


    public void putDataInFile() {

        if (time <= 0) {
            File.WriteAllText("output.txt", "Infinitely small");
        }else {
            File.WriteAllText("output.txt", time.ToString());
        }
        if (time == 1000000000) {
            File.WriteAllText("output.txt", "Infinitely big");
        }


    }

}

