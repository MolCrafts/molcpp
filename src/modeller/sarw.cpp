#include "modeller/sarw.h"

namespace molcpp
{
    SARW::SARW(size_t x, size_t y, size_t z, double max_density=0.05) : _x(x), _y(y), _z(z), _n_sites(x * y * z), _occupied(0), _max_density(max_density)
    {
        allocate(x, y, z);
    }

    void SARW::allocate(size_t x, size_t y, size_t z)
    {
        /* Initialize the sites as empty */
        site.resize(x, std::vector<std::vector<std::array<size_t, 4>>>(y, std::vector<std::array<size_t, 4>>(z)));
        loc_dens.resize(x, std::vector<std::vector<std::array<size_t, 4>>>(y, std::vector<std::array<size_t, 4>>(z)));
        snd_dens.resize(x, std::vector<std::vector<std::array<size_t, 4>>>(y, std::vector<std::array<size_t, 4>>(z)));
        for (size_t i = 0; i < x; i++)
        {
            for (size_t j = 0; j < y; j++)
            {
                for (size_t k = 0; k < z; k++)
                {
                    for (size_t m = 0; m < 4; m++)
                    {
                        site[i][j][k][m] = 0;
                        loc_dens[i][j][k][m] = 0;
                        snd_dens[i][j][k][m] = 0;
                    }
                }
            }
        }
    }

    std::vector<coord> SARW::single(size_t length)
    {
        // Check density
        double density = (_occupied + length) / _n_sites;
        if (density > _max_density)
        {
            throw ValueError("Density is too high");
        }
        else
        {
            _density = density;
            std::string msg = "Density is " + std::to_string(_density);
            LOG_INFO(msg);
        }

        size_t i, j, k, m, u, v;
        int ii, jj, kk, mm, nn, n;
        int n_oc_sites, t_sites;
        int dx[3], dy[3], dz[3];
        int st_ld[12][4];
        int snd_ld[6][4];
        int snd_count, nn_count, total_dens, point;
        int prob_low, prob_high;
        int reset;
        double sqrt_2_2;
        double angle, va_mag, vb_mag, d_prod;
        double a[3], aa[3], va[3], vb[3], vc[3];
        double neigh[12][4], v_store[12][3], mag_store[12];
        char buf[256];
        std::vector<coord> xyz(length);
        std::vector<size_t> spot(length);
        std::default_random_engine generator;
        std::uniform_int_distribution<size_t> genx(0, _x);
        std::uniform_int_distribution<size_t> geny(0, _y);
        std::uniform_int_distribution<size_t> genz(0, _z);
        std::uniform_int_distribution<size_t> genm(0, 4);

        /* Determine the edge lengths in lattice units  from the density */
        sqrt_2_2 = sqrt(2) / 2.0;
        // for (u = 0; u < n_chains; u++)
        // {
        // atom_list[natom].chain = u + 1;
        // atom_list[natom].nic = 0;
        do
        {
            i = genx(generator);
            j = geny(generator);
            k = genz(generator);
            m = genm(generator);
        } while (site[i][j][k][m]);

        // if (site[i][j][k][m] == 1)
        // {
        //     u--;
        // }
        // else
        // {
        // atom_list[natom].x[0] = i;
        // atom_list[natom].x[1] = j;
        // atom_list[natom].x[2] = k;
        // atom_list[natom].spot = m;
        // atom_list[natom].type = 1;
        xyz[0] = {i, j, k};
        spot[0] = m;
        site[i][j][k][m] = 1;

        for (v = 1; v < length; v++)
        {
            // printf("looking for neighbor %d \n", v);
            nn = 0;
            nn_count = 0;
            snd_count = 0;
            angle = 0;
            dx[1] = i;
            dy[1] = j;
            dz[1] = k;
            dx[2] = i + 1;
            dy[2] = j + 1;
            dz[2] = k + 1;
            dx[0] = i - 1;
            dy[0] = j - 1;
            dz[0] = k - 1;
            if (dx[2] == _x)
            {
                dx[2] = 0;
            }
            if (dy[2] == _y)
            {
                dy[2] = 0;
            }
            if (dz[2] == _z)
            {
                dz[2] = 0;
            }
            if (dx[0] < 0)
            {
                dx[0] = _x - 1;
            }
            if (dy[0] < 0)
            {
                dy[0] = _y - 1;
            }
            if (dz[0] < 0)
            {
                dz[0] = _z - 1;
            }

            if (m == 0)
            {
                a[0] = 0;
                a[1] = 0;
                a[2] = 0;
            }
            else if (m == 1)
            {
                a[0] = 0.5;
                a[1] = 0.5;
                a[2] = 0;
            }
            else if (m == 2)
            {
                a[0] = 0.5;
                a[1] = 0;
                a[2] = 0.5;
            }
            else
            {
                a[0] = 0;
                a[1] = 0.5;
                a[2] = 0.5;
            }
            for (ii = 0; ii < 3; ii++)
            {
                for (jj = 0; jj < 3; jj++)
                {
                    for (kk = 0; kk < 3; kk++)
                    {
                        for (mm = 0; mm < 4; mm++)
                        {
                            if (mm == 0)
                            {
                                aa[0] = 0;
                                aa[1] = 0;
                                aa[2] = 0;
                            }
                            else if (mm == 1)
                            {
                                aa[0] = 0.5;
                                aa[1] = 0.5;
                                aa[2] = 0;
                            }
                            else if (mm == 2)
                            {
                                aa[0] = 0.5;
                                aa[1] = 0;
                                aa[2] = 0.5;
                            }
                            else if (mm == 3)
                            {
                                aa[0] = 0;
                                aa[1] = 0.5;
                                aa[2] = 0.5;
                            }
                            aa[0] = aa[0] + ii - 1;
                            aa[1] = aa[1] + jj - 1;
                            aa[2] = aa[2] + kk - 1;
                            va[0] = (double)aa[0] - (double)a[0];
                            va[1] = (double)aa[1] - (double)a[1];
                            va[2] = (double)aa[2] - (double)a[2];
                            va_mag = sqrt(va[0] * va[0] + va[1] * va[1] + va[2] * va[2]);
                            if (site[dx[ii]][dy[jj]][dz[kk]][mm] == 0 || (v == length - 1 && site[dx[ii]][dy[jj]][dz[kk]][mm] == 2))
                            {
                                if (va_mag <= sqrt_2_2 + .01)
                                {
                                    loc_dens[dx[ii]][dy[jj]][dz[kk]][mm]++;
                                    st_ld[nn_count][0] = dx[ii];
                                    st_ld[nn_count][1] = dy[jj];
                                    st_ld[nn_count][2] = dz[kk];
                                    st_ld[nn_count][3] = mm;
                                    nn_count++;
                                }
                                /*
                                                              else if(va_mag<=1.01)
                                                                {
                                                                  snd_dens[dx[ii]][dy[jj]][dz[kk]][mm]++;
                                                                  snd_ld[snd_count][0]=dx[ii];
                                                                  snd_ld[snd_count][1]=dy[jj];
                                                                  snd_ld[snd_count][2]=dz[kk];
                                                                  snd_ld[snd_count][3]=mm;
                                                                  snd_count++;
                                                                }
                                */
                                if (va_mag < sqrt_2_2)
                                {
                                    // printf("creating atoms too close to each other\n");
                                    exit(1);
                                }
                                if (va_mag <= sqrt_2_2 + .01)
                                {
                                    if (v != 1)
                                    {
                                        d_prod = va[0] * vb[0] + va[1] * vb[1] + va[2] * vb[2];
                                        angle = acos(d_prod / (va_mag * vb_mag)) * 180.0 / PI;
                                    }
                                    if ((angle < -60.0 && angle > -150.0) || (angle > 60.0 && angle < 150.0) || v == 1)
                                    {
                                        neigh[nn][0] = dx[ii];
                                        neigh[nn][1] = dy[jj];
                                        neigh[nn][2] = dz[kk];
                                        neigh[nn][3] = mm;
                                        v_store[nn][0] = va[0];
                                        v_store[nn][1] = va[1];
                                        v_store[nn][2] = va[2];
                                        mag_store[nn] = va_mag;
                                        nn++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (nn == 0)
            {
                if (reset == 1)
                {
                    // printf("has already been reset and still can not find a neighbor\n");
                    // printf("chain %d atom %d \n", u, v);
                    exit(1);
                }
                // printf("there is not a free neighbor site and must reset\n");
                reset = 1;
                site[i][j][k][m] = 2;
                // i = atom_list[natom].x[0];
                // j = atom_list[natom].x[1];
                // k = atom_list[natom].x[2];
                // m = atom_list[natom].spot;
                i = xyz[v - 1][0];
                j = xyz[v - 1][1];
                k = xyz[v - 1][2];
                m = spot[v - 1];
                for (ii = 0; ii < 12; ii++)
                {
                    loc_dens[st_ld[ii][0]][st_ld[ii][1]][st_ld[ii][2]][st_ld[ii][3]]--;
                }
                /*
                                  for(ii=0;ii<6;ii++)
                                    {
                                      snd_dens[snd_ld[ii][0]][snd_ld[ii][1]][snd_ld[ii][2]][snd_ld[ii][3]]--;
                                    }
                */
                vb[0] = vc[0];
                vb[1] = vc[1];
                vb[2] = vc[2];
                v = v - 2;
            }
            else
            {
                total_dens = 0;
                for (ii = 0; ii < nn; ii++)
                {
                    total_dens = total_dens + (12 - loc_dens[st_ld[ii][0]][st_ld[ii][1]][st_ld[ii][2]][st_ld[ii][3]]);
                    /*
                                          total_dens=total_dens+(6-snd_dens[st_ld[ii][0]][st_ld[ii][1]][st_ld[ii][2]][st_ld[ii][3]]);
                    */
                }
                point = total_dens * ((double)rand() / (double)RAND_MAX);
                prob_low = 0;
                prob_high = (12 - loc_dens[st_ld[0][0]][st_ld[0][1]][st_ld[0][2]][st_ld[0][3]]);
                /*
                                  prob_high=prob_high+(6-snd_dens[st_ld[0][0]][st_ld[0][1]][st_ld[0][2]][st_ld[0][3]]);
                */
                // printf("span %d prob_high %d prob_low %d point %d\n", prob_high - prob_low, prob_high, prob_low, point);
                // printf("0 %d 1 %d 2 %d 3 %d \n", st_ld[0][0], st_ld[0][1], st_ld[0][2], st_ld[0][3]);
                // printf("site %d\n", site[st_ld[0][0]][st_ld[0][1]][st_ld[0][2]][st_ld[0][3]]);
                for (ii = 0; ii < nn; ii++)
                {
                    if (point >= prob_low && point < prob_high)
                    {
                        i = neigh[ii][0];
                        j = neigh[ii][1];
                        k = neigh[ii][2];
                        m = neigh[ii][3];
                        // atom_list[natom].x[0] = i;
                        // atom_list[natom].x[1] = j;
                        // atom_list[natom].x[2] = k;
                        // atom_list[natom].spot = m;
                        // atom_list[natom].type = 1;
                        // atom_list[natom].chain = u + 1;
                        xyz[v][0] = i;
                        xyz[v][1] = j;
                        xyz[v][2] = k;
                        spot[v] = m;
                        site[i][j][k][m] = 1;

                        /*store the previous vector*/
                        vc[0] = vb[0];
                        vc[1] = vb[1];
                        vc[2] = vb[2];
                        vb[0] = -v_store[ii][0];
                        vb[1] = -v_store[ii][1];
                        vb[2] = -v_store[ii][2];
                        vb_mag = mag_store[ii];
                        ii = nn;
                        reset = 0;
                    }
                    else
                    {
                        if (ii == nn - 1)
                        {
                            if (reset == 1)
                            {
                                // printf("there is not a free neighbor site and must reset\n");
                                // printf("has already been reset and still can not find a neighbor\n");
                                // printf("chain %d atom %d \n", u, v);
                                exit(1);
                            }
                            // printf("resetting\n");
                            reset = 1;
                            site[i][j][k][m] = 2;
                            // i = atom_list[natom].x[0];
                            // j = atom_list[natom].x[1];
                            // k = atom_list[natom].x[2];
                            // m = atom_list[natom].spot;
                            i = xyz[v - 1][0];
                            j = xyz[v - 1][1];
                            k = xyz[v - 1][2];
                            m = spot[v - 1];
                            for (ii = 0; ii < 12; ii++)
                            {
                                loc_dens[st_ld[ii][0]][st_ld[ii][1]][st_ld[ii][2]][st_ld[ii][3]]--;
                            }
                            /*
                                                           for(ii=0;ii<6;ii++)
                                                             {
                                                               snd_dens[snd_ld[ii][0]][snd_ld[ii][1]][snd_ld[ii][2]][snd_ld[ii][3]]--;
                                                             }
                            */
                            vb[0] = vc[0];
                            vb[1] = vc[1];
                            vb[2] = vc[2];
                            ii = nn;
                            v = v - 2;
                        }
                        else
                        {
                            prob_low = prob_high;
                            prob_high = prob_high + (12 - loc_dens[st_ld[ii + 1][0]][st_ld[ii + 1][1]][st_ld[ii + 1][2]][st_ld[ii + 1][3]]);
                            /*
                                                          prob_high=prob_high+(6-snd_dens[st_ld[ii+1][0]][st_ld[ii+1][1]][st_ld[ii+1][2]][st_ld[ii+1][3]]);
                            */
                        }
                    }
                }
            }
        }

        _occupied += length;

        return xyz;
    }

}