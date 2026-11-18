/*
 * shae-ada-flight-calculator
 *
 * An Ada-strongly-typed CLI trajectory calculator conforming to the
 * SHAE Field Manual design system.
 *
 * Usage:
 *   shae-ada-flight-calculator <velocity> <angle_deg> <gravity>
 *
 * Outputs: time of flight, max height, horizontal range, impact
 * velocity, and a position table sampled at 10 ms intervals.
 *
 * Invalid input -> clear error on stderr, exit code 1.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

static void fail(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fputc('\n', stderr);
    exit(1);
}

static double pos_num(const char *token, const char *what) {
    char *endp = NULL;
    double v = strtod(token, &endp);
    if (endp == token || *endp != '\0') {
        fail("invalid %s: '%s' is not a number", what, token);
    }
    if (!isfinite(v)) {
        fail("invalid %s: '%s' is not finite", what, token);
    }
    if (v <= 0.0) {
        fail("%s must be a positive number (got %g)", what, v);
    }
    return v;
}

int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr,
            "usage: %s <velocity> <angle_deg> <gravity>\n"
            "  velocity   Initial speed in m/s (positive number)\n"
            "  angle_deg  Launch angle in degrees (0 < angle < 90)\n"
            "  gravity    Acceleration due to gravity in m/s^2 (positive number)\n",
            argv[0]);
        return 1;
    }

    double v0 = pos_num(argv[1], "velocity");
    double angle_deg = pos_num(argv[2], "angle");
    double g = pos_num(argv[3], "gravity");

    if (angle_deg >= 90.0) {
        fail("angle must be less than 90 degrees (got %g)", angle_deg);
    }

    double theta = angle_deg * M_PI / 180.0;
    double vx = v0 * cos(theta);
    double vy = v0 * sin(theta);

    double t_flight = 2.0 * vy / g;
    double max_h = vy * vy / (2.0 * g);
    double range = vx * t_flight;

    /* At time of flight the vertical component is -vy by symmetry. */
    double impact_vy = vy - g * t_flight;
    double impact_speed = sqrt(vx * vx + impact_vy * impact_vy);
    double impact_angle = -angle_deg;

    printf("Input parameters:\n");
    printf("  Initial velocity : %.6f m/s\n", v0);
    printf("  Launch angle     : %.6f degrees\n", angle_deg);
    printf("  Gravity          : %.6f m/s^2\n", g);
    printf("\nTrajectory results:\n");
    printf("  Time of flight   : %.6f s\n", t_flight);
    printf("  Max height       : %.6f m\n", max_h);
    printf("  Horizontal range : %.6f m\n", range);
    printf("  Impact velocity  : %.6f m/s at %.6f degrees\n",
           impact_speed, impact_angle);

    /* Position table sampled at 10 ms intervals. */
    const double dt = 0.01;
    printf("\nPosition table (dt = 10 ms):\n");
    printf("  time(s)        x(m)          y(m)          vx(m/s)     vy(m/s)\n");
    for (double t = 0.0; t <= t_flight + 1e-9; t += dt) {
        double x = vx * t;
        double y = vy * t - 0.5 * g * t * t;
        double vy_t = vy - g * t;
        if (y < 0.0) break;
        printf("  %.4f       %.6f     %.6f    %.6f    %.6f\n",
               t, x, y, vx, vy_t);
    }

    return 0;
}
