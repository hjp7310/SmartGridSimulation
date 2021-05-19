simple PowerPlant
{
    gates:
        input in;
        output out;
}

simple Substation
{
    gates:
        input in;
        output out;
}

simple Consumer
{
    gates:
        input in;
        output out;
}

network Topology
{
    submodules:
        pp1: PowerPlant;
        pp2: PowerPlant;
        ss1: Substation;
        ss2: Substation;
        c1: Consumer;
        c2: Consumer;
        c3: Consumer;
    connections:
        pp1.out --> ss1.in;
        pp1.in <-- ss1.out;
        pp2.out --> ss1.in;
        pp2.in <-- ss1.out;
        ss1.out --> ss2.in;
        ss1.in <-- ss2.out;
        ss2.out --> c1.in;
        ss2.in <-- c1.out;
        ss2.out --> c2.in;
        ss2.in <-- c2.out;
        ss2.out --> c3.in;
        ss2.in <-- c3.out;
}
