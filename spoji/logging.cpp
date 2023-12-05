#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

class Logger
{
public:
    Logger(const string &filename)
    {
        logFile.open(filename, ios::out | ios::app);
        if (!logFile.is_open())
        {
            cerr << "Error opening log file: " << filename << endl;
        }
    }

    ~Logger()
    {
        if (logFile.is_open())
        {
            logFile.close();
        }
    }

    void log(const string &message)
    {
        writeLog("LOG", message);
    }

    void debug(const string &message)
    {
        writeLog("DEBUG", message);
    }

    void info(const string &message)
    {
        writeLog("INFO", message);
    }

    void error(const string &message)
    {
        writeLog("ERROR", message);
    }

private:
    ofstream logFile;

    void writeLog(const string &level, const string &message)
    {
        time_t now = time(0);
        tm *timeinfo = localtime(&now);
        char timestamp[80];
        strftime(timestamp, sizeof(timestamp), "[%Y-%m-%d %H:%M:%S] ", timeinfo);

        cout << timestamp << "[" << level << "] " << message << endl;

        if (logFile.is_open())
        {
            logFile << timestamp << "[" << level << "] " << message << endl;
            logFile.flush();
        }
    }
};

class Matrix
{
public:
    Matrix(int rows, int cols) : rows(rows), cols(cols), data(rows * cols) {}

    Matrix operator+(const Matrix &other) const
    {
        if (rows != other.rows || cols != other.cols)
        {
            throw invalid_argument("Matrices must have the same dimensions for addition.");
        }

        Matrix result(rows, cols);
        logger.log("Performing matrix addition.");

        for (int i = 0; i < rows * cols; ++i)
        {
            result.data[i] = data[i] + other.data[i];
        }

        return result;
    }

    Matrix operator-(const Matrix &other) const
    {
        if (rows != other.rows || cols != other.cols)
        {
            throw invalid_argument("Matrices must have the same dimensions for subtraction.");
        }

        Matrix result(rows, cols);
        logger.log("Performing matrix subtraction.");

        for (int i = 0; i < rows * cols; ++i)
        {
            result.data[i] = data[i] - other.data[i];
        }

        return result;
    }

    Matrix operator*(const Matrix &other) const
    {
        if (cols != other.rows)
        {
            throw invalid_argument("Number of columns in the first matrix must be equal to the number of rows in the second matrix for multiplication.");
        }

        Matrix result(rows, other.cols);
        logger.log("Performing matrix multiplication.");

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < other.cols; ++j)
            {
                for (int k = 0; k < cols; ++k)
                {
                    result.data[i * result.cols + j] += data[i * cols + k] * other.data[k * other.cols + j];
                }
            }
        }

        return result;
    }

    Matrix operator/(const Matrix &other) const
    {
        // Assuming division is element-wise
        if (rows != other.rows || cols != other.cols)
        {
            throw invalid_argument("Matrices must have the same dimensions for element-wise division.");
        }

        Matrix result(rows, cols);
        logger.log("Performing matrix element-wise division.");

        for (int i = 0; i < rows * cols; ++i)
        {
            if (other.data[i] == 0)
            {
                throw invalid_argument("Division by zero encountered.");
            }
            result.data[i] = data[i] / other.data[i];
        }

        return result;
    }

private:
    int rows;
    int cols;
    vector<int> data;

    static Logger logger;
};

Logger Matrix::logger("matrix_log.txt");

int main()
{
    try
    {
        Matrix A(2, 2);
        Matrix B(2, 2);

        Matrix C = A + B;
        Matrix D = A - B;
        Matrix E = A * B;
        Matrix F = A / B;
    }
    catch (const exception &e)
    {
        cerr << "Exception: " << e.what() << endl;
    }

    return 0;
}
