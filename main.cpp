#include <iostream>
#include <fstream>
using namespace std;
ifstream f("date.in");

struct tranzitie
{
    int primul;
    int ultimul;
    char litera;

};

struct stare_rez
{
    int lungime=0;
    int vect[30];

};

struct tranz_AFD
{

    stare_rez prim;
    stare_rez ultim;
    char lit;

};

void ordonare(int v[30], int n)
{
    for(int j=0; j<n-1; j++)
        for(int i=j+1; i<n; i++)
        {
            if(v[j]>v[i])
                swap(v[j], v[i]);
        }

}

bool comparare(stare_rez r1, stare_rez r2)///1 pt egalitate
{
    if(r1.lungime!=r2.lungime)
        return 0;
    for(int i=0; i<r1.lungime; i++)
    {
        if(r1.vect[i]!=r2.vect[i])
            return 0;
    }

    return 1;

}

void eliminare(int v[30], int n, int k)
{
    if(k==n-1)
        v[k]=-1;

    else
    {
        for(int i=k; i<n-1; i++)
            v[i]=v[i+1];

    }
}

int reuniune(int v[30], int n)
{
    int i;
    for(int j=0; j<n-1; j++)
        for( i=j+1; i<n; i++)
        {
            if(v[j]==v[i])
            {
                eliminare(v, n, i);
                n--;
                ///cout<<"in fct n= "<<n<<"\n";
            }
        }

    return n;
}

int main()
{

    int  poz, poz_ad, final_final[30];
    tranz_AFD afd[30];
    int nr_stari, i, j,stari_fin[10]= {0}, nr_lit, stare_init, nr_finale, nr_tranz, x, y, n, ok, k, t;
    char alfabet[5], lit;
    tranzitie tr[30];
    stare_rez r[30];


    f>>nr_stari;
    f>>stare_init;
    f>>nr_finale;///nr stari finale

    ///vectorul pt stari finale
    for(i=1; i<=nr_finale; i++)
    {
        f>>j;

        stari_fin[j]=1;
    }



    f>>nr_lit;
    ///alfabetul
    for(i=0; i<nr_lit; i++)
    {
        f>>lit;
        alfabet[i]=lit;
    }
    f>>nr_tranz;
    for(i=0; i<nr_tranz; i++)
    {
        f>>x>>y>>lit;
        tr[i].primul=x;
        tr[i].ultimul=y;
        tr[i].litera=lit;
    }


    for(i=0; i<nr_tranz; i++)
    {

        cout<<tr[i].primul<<" ";
        cout<<tr[i].ultimul<<" ";
        cout<<tr[i].litera<<endl;
    }



    poz=0;
    poz_ad=1;
    r[poz].lungime=1;
    r[poz].vect[0]=stare_init;
    // vect[poz]=stare_init;
    //poz++;
    i=0;

    while(i<=poz_ad)
    {cout<<"suntem in while, i= "<<i<<"\n";
        for(j=0; j<nr_lit; j++)
        {cout<<"suntem in for, j= "<<j<<"\n";
            for(k=0; k<r[i].lungime; k++)
            {cout<<"suntem in for, k= "<<k<<"\n";
                for(t=0; t<nr_tranz; t++)
                  {
                   cout<<"suntem in for, t= "<<t<<"\n";
                    if( tr[t].primul==r[i].vect[k]  && tr[t].litera ==alfabet[j])
                    {cout<<"am gasit tr-"<<t<<"\n";
                        r[poz_ad].vect[r[poz_ad].lungime]=tr[t].ultimul; // verif
                        cout<<"am adaugat "<<tr[t].ultimul<<" pe poz "<<r[poz_ad].lungime<<" lui r"<<poz_ad<<"\n";
                        r[poz_ad].lungime++;
                    }
                  }
            ///}
            ///rafinare:

            n=reuniune(r[poz_ad].vect,r[poz_ad].lungime );
            r[poz_ad].lungime=n;
            ordonare(r[poz_ad].vect,r[poz_ad].lungime);

            ///verificare sa nu se repete, dc se repeta, nu cresc pozitia de ad, sterg vect si fac lungimea 0 la loc
            ok=0;
            for(int w=0; w<poz_ad; w++)
                if(comparare(r[poz_ad], r[w]))
                {
                    ok=1;
                    //break;
                }
            if(ok)
            {
                r[poz_ad].lungime=0;
                // delete[] r[poz_ad].vect;
            }
            else
            {

                afd[poz_ad].prim=r[i];
                afd[poz_ad].ultim=r[poz_ad];
                afd[poz_ad].lit=alfabet[j];

            }if(ok==0)
            poz_ad++;
            }

        }

        i++;
    }








///initalizare vector stari finale afd:

    for(i=0; i<poz_ad; i++)
        final_final[i]=0;

    ///verificare stare finala:

    for(k=0; k<poz_ad; k++)

        for(i=0; i<nr_finale; i++)
        {
            if(stari_fin[i]==1)
                for(j=1; j<r[k].lungime; j++)
                {
                    if(i==r[k].vect[j])
                    {
                        final_final[k]=1;///initializeaza vectorul asta
                        ///break;
                    }
                }
        }


///afisare:
    cout<<"noile noduri: ";
    for(i=1; i<=poz_ad; i++)
    {
        cout<<"tranzitie de la q";
        for(j=0; j<afd[i].prim.lungime; j++)
        {
            cout<<afd[i].prim.vect[j];

        }cout<<" ";
        if(final_final[i]==1)
            cout<<"<---stare finala ";

        cout<<" pana la q";
        for(j=0; j<afd[i].ultim.lungime; j++)
        {
            cout<<afd[i].ultim.vect[j];

        }cout<<" ";
        if(final_final[i]==1)
            cout<<"<---stare finala ";

        cout<<"litera "<<afd[i].lit;


        cout<<"\n";
    }


///--------------------------------------------------------------------------



    /**
    while(poz<=poz_ad)
    {
        r[poz+1].lungime=0;/// initializata la inceput????
        for(i=0; i<nr_lit; i++)
        {
            if(tr[vect[poz]].litera==alfabet[i])

            {
                r[poz+1].vect[r[poz+1].lungime]=tr[vect[poz]].ultimul;
                r[poz+1].lungime++;
            }
            r[poz+1].lungime=reuniune(r[poz+1].vect, r[poz+1].lungime);///aranjam vectorul
            ordonare(r[poz+1].vect, r[poz+1].lungime);

            for(j=0; j<poz; j++)
            {

                if(comparare(r[j], r[poz+1])==0)///nu am apelat bine pt ca urmeaza stari compuse
                {
                    vect[poz_ad]=r[poz+1].vect;
                    poz_ad++;
                }
            }
            afd[poz].lit=alfabet[i];
            afd[poz].prim=r[poz];
            afd[poz].prim=r[poz+1];
        }

        poz++;
    }
    */


    /**

        int n=6;
        for(int i=0;i<n;i++)
            cin>>vect[i];
        cout<<" ";
        cout<<"n= "<<n<<"\n";
        n=reuniune(vect,n);
        cout<<"n= "<<n<<"\n";
        ordonare(vect, n);
        for(int i=0;i<n;i++)
            cout<<vect[i];




    -------------------



    5
    2 14 6 7 1
    5
    2 14 6 7 1
    3
    5 6 8


    -----------------
    stare_rez r[3];
    for(i=0;i<3;i++)
    {
        f>>r[i].lungime;
        for(j=0; j < r[i].lungime; j++)
            f>>r[i].vect[j];
    }
    for(i=0;i<3;i++)
    {
        cout<<"lungime= "<<r[i].lungime<<"\n";
        for(j=0; j < r[i].lungime; j++)
            cout<<r[i].vect[j]<<" ";
            cout<<"\n";
    }
    cout<<comparare(r[0], r[1]);
    cout<<" ";
    cout<<comparare(r[1], r[2]);
    */
}
