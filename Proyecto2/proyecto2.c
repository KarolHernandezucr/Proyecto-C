/* El programa recibe los coeficientes de dos ecuaciones
cuadraticas y el porcentaje de error que el usuario decida,
luego calcula el subdominio en el que la diferencia
entre ambas funciones es menor al porcentaje de error
y muestra la gráfica de ambas funciones, así como
el subdominio en el que la diferencia entre ambas funciones
es menor al porcentaje de error.
Hecho por: 
Oscar Francisco Rojas Rojas  C36953
Karol Hernández Morera       B63367
Steven Ruiz Urbina           B97029
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double funcion_cuadratica(double a, double b, double c, double x) {
    // Devuelve la imagen de una funcion cuadratica
    return a * x * x + b * x + c;
}


double calcular_error(double a, double b, double c, double d, double e, double f, double x) {
    // Calcula el porcentaje de error entre ambas funciones
    double imagen_f = funcion_cuadratica(a, b, c, x);
    double imagen_g = funcion_cuadratica(d, e, f, x);

    if (imagen_f == 0) {
        return INFINITY;  // Se evita la division por 0
    } else {
        double error = 100 * (imagen_g - imagen_f) / imagen_f;
        return fabs(error);  // Valor absoluto
    }
}

int graficar(double a, double b, double c, double d, double e, double f, double porcentaje_error) {
    // Grafica ambas funciones y el subdominio
    FILE *fp = popen("gnuplot", "w");  // Tuberia con gnuplot

    if (fp == NULL) {
        printf("Error al abrir la tubería con gnuplot\n");
        return 0; // El 0 indica que hubo un error
    }

    fprintf(fp, "set title 'Gráfica de dos Ecuaciones Cuadráticas'\n");  // Titulo
    fprintf(fp, "set xlabel 'x'\n");  // Eje X
    fprintf(fp, "set ylabel 'y'\n");  // Eje Y
    fprintf(fp, "f(x) = %f * x**2 + %f * x + %f\n", a, b, c);  // Funcion f(x)
    fprintf(fp, "g(x) = %f * x**2 + %f * x + %f\n", d, e, f);  // Funcion g(x)

    // Imprimir datos de la función f
    fprintf(fp, "plot f(x) title 'Función f', g(x) title 'Función g'\n");

    double start_x = -100000, end_x = 100000;  // Dominio
    int intervalo = 0;  // Indicador de donde empieza el subdominio (0 : False)

    // Imprimir datos de la función f
    for (double x = -100000; x <= 100000; x += 0.1) {
        double error = calcular_error(a, b, c, d, e, f, x);  // Obtener error

        if (error <= porcentaje_error && !intervalo) {
            start_x = x;  // Inicia el subdominio
            intervalo = 1;  // Indicador de que empieza el subdominio (True)
        }

        if (intervalo && (error > porcentaje_error || x >= 100000)) {
            end_x = x;  // Termina subdominio
            // Subdominio en color verde
            fprintf(fp, "set object rect from %f, graph 0 to %f, graph 1 fc rgb 'green' fillstyle solid border -1\n", start_x, end_x);
            intervalo = 0;  // Indicador de subdominio = False
        }

        if (error > porcentaje_error && intervalo) {
            end_x = x - 0.1;
            // Flecha desde el punto de de inicio del subdominio hasta el punto final del subdominio
            fprintf(fp, "set arrow from %f,%f to %f,%f nohead lc rgb 'red'\n", start_x, funcion_cuadratica(a, b, c, start_x), end_x, funcion_cuadratica(a, b, c, end_x));
            intervalo = 0;
        }
    }

    // Imprimir datos de la función g
    for (double x = -100000; x <= 100000; x += 0.1) {
        fprintf(fp, "%f %f\n", x, funcion_cuadratica(d, e, f, x));
    }

    if (start_x == -100000 && end_x == 100000) {
        printf("No existe subdominio para las ecuaciones dadas.\n");
    } else {
        printf("Subdominio: [%.2f, %.2f]\n", start_x, end_x);
    }

    fflush(fp);  // Limpieza de datos
    getchar();  // Esperar a que se presione Enter
    pclose(fp);  // Cerrar tuberia

    return 0;
}

int main() {
    double a, b, c, d, e, f;
    double porcentaje_error;

    // Ingresar coeficientes de la función f
    printf("Ingrese los coeficientes de la función f (ax^2 + bx + c):\n");
    printf("a: ");
    scanf("%lf", &a);
    printf("b: ");
    scanf("%lf", &b);
    printf("c: ");
    scanf("%lf", &c);

    // Ingresar coeficientes de la función g
    printf("\nIngrese los coeficientes de la función g (dx^2 + ex + f):\n");
    printf("d: ");
    scanf("%lf", &d);
    printf("e: ");
    scanf("%lf", &e);
    printf("f: ");
    scanf("%lf", &f);

    // Ingresar porcentaje de error
    printf("\nIngrese el porcentaje de error (0-100): ");
    scanf("%lf", &porcentaje_error);

    // CCalcular y graficar el subdominio
    int subdominio_encontrado = graficar(a, b, c, d, e, f, porcentaje_error);

    return 0;
}
