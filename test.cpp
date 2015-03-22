#include "test.h"

string breed[20] = {
    "Chihuahua","Japanese_spaniel","Maltese_dog","Pekinese","Shih-Tzu",
"Blenheim_spaniel","papillon","toy_terrier","Rhodesian_ridgeback","basset",
"beagle","bloodhound","Walker_hound","English_foxhound","Irish_wolfhound",
    "whippet", "Pomeranian", "samoyed", "labrador", "bichon"
};

string image_1, image_2, image_3;
int image_number = 0;
int image_number_2 = 0;
int image_number_3 = 0;

std::vector<double> test::read_pgm(std::ifstream& file) {
    std::vector<double> values;
    std::string str;
    file >> str;// Skip P2 line
    file >> str;// Skip width line
    file >> str;// Skip height line
    file >> str;// Skip max value line

    int val;
    while(file >> val)
    {
        values.push_back(val);
    }
    return values;
}

std::vector< std::vector<double> > test::read_training_data() {
    std::vector< std::vector<double> > array;

    // Iteration over people.
    for (int face = 0; face < Faces; ++face)
    {
        std::vector< std::vector<double> > facearray;
        // Iteration over photos.
        for (int sample = 0; sample < Samples; ++sample)
        {
            std::stringstream filename;
            filename << DataPath << "s" << face + 1 << "/" << sample  + 1 << ".pgm";
            std::ifstream image(filename.str().c_str());

            if (image.is_open()) {
                facearray.push_back(read_pgm(image));
                image.close();
            } else {
                std::cout << "Image was not opened.";
            }
        }
        // Find the mean image.
        std::vector<double> mean;
        for (int i = 0; i < M; ++i)
        {
            double sum = 0;
            for (int j = 0; j < Samples; ++j)
            {
                sum += facearray[j][i];
            }
            mean.push_back(sum/Samples);
        }
        array.push_back(mean);
    }
    return array;
}

int test::recognize(Matrix X, Matrix B, Matrix U, Matrix W) {
    /* Subtract the mean image */
    for (int c = 0; c < M; ++c)
    {
        X.array[0][c] -= B.array[0][c];
        if (X.array[0][c] < 0)
        {
            X.array[0][c] = 0;
        }
    }

    /* Find weights */
    Matrix Wx = Matrix(Eigenfaces, 1);

    for (int r = 0; r < Eigenfaces; ++r)
    {
        Wx.array[r][0] = (U.getRow(r)*X.transpose()).array[0][0];
    }

    /* Find the closest face from the trainig set */
    double min_distance = DBL_MAX;
    double min_distance_2 = DBL_MAX;
    double min_distance_3 = DBL_MAX;

    for (int image = 0; image < N; ++image)
    {
        double distance = 0;
        for (int eigenface = 0; eigenface < Eigenfaces; ++eigenface)
        {
            distance += fabs(W.array[eigenface][image] - Wx.array[eigenface][0]);
        }
        if (distance < min_distance || image == 0)
        {
            min_distance_3 = min_distance_2;
            min_distance_2 = min_distance;
            min_distance = distance;

            image_number_3 = image_number_2;
            image_number_2 = image_number;
            image_number = image;
        }

        else if (distance >=  min_distance && distance < min_distance_2) {
            min_distance_3 = min_distance_2;
            min_distance_2 = distance;

            image_number_3 = image_number_2;
            image_number_2 = image;
        }
        else if (distance >= min_distance_2 && distance < min_distance_3) {
            min_distance_3 = distance;
            image_number_3 = image;
        }
    }

    return 1;
}

int test::test_image(string fileName)
{
    Matrix A = Matrix(N, M, read_training_data());
    Matrix B = Matrix(1, M);

    /* Find the mean image */
    for (int c = 0; c < M; ++c)
    {
        double sum = 0;
        for (int r = 0; r < N; ++r)
        {
            sum += A.array[r][c];
        }
        B.array[0][c] = sum/N;
    }
    /* Subtract the mean from each image */
    for (int r = 0; r < N; ++r)
    {
        for (int c = 0; c < M; ++c)
        {
            A.array[r][c] -= B.array[0][c];
            if (A.array[r][c] < 0)
            {
                A.array[r][c] = 0;
            }
        }
    }
    /* Find the covariance matrix */
    Matrix S = A * A.transpose();

    /* Find eigenvectors of the covariance matrix */
    Matrix V = eigensystem(&S).second.transpose();

    /* Find eigenfaces */
    Matrix U = Matrix(Eigenfaces, M);

    for (int r = 0; r < Eigenfaces; ++r)
    {
        Matrix eigenface = V.getRow(r)*A;

        U.array[r] = eigenface.array[0];
        double norm = 0;
        for (int i = 0; i < U.columns; i++) {
            norm += pow(U.array[r][i], 2);
        }
        norm = sqrt(norm);
        for (int i = 0; i < U.columns; i++) {
            U.array[r][i] /= norm;
        }
    }

    /* Find weights */
    Matrix W = Matrix(Eigenfaces, N);
    for (int r = 0; r < Eigenfaces; ++r)
    {
        for (int c = 0; c < N; ++c)
        {
            W.array[r][c] = (U.getRow(r)*A.getRow(c).transpose()).array[0][0];
        }
    }
    /* Classify the image from the arguments */
    std::ifstream image(fileName.c_str());
    std::vector< std::vector<double> > array;
    if (image.is_open()) {
        array.push_back(read_pgm(image));
        image.close();
    } else {
        std::cout << "Error: could not open image specified in the arguments.";
        return 0;
    }

    Matrix X = Matrix(1, M, array);
    recognize(X, B, U, W);

    image_1 = breed[image_number];
    image_2 = breed[image_number_2];
    image_3 = breed[image_number_3];

    return 0;
}


