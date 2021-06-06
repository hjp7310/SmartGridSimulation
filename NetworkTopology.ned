simple ControlCenter
{
    gates:
        inout control_gate[];
        inout power_gate[];
}

simple PowerPlant
{
    gates:
        inout control_gate[];
        output power_gate_out[];
}

simple Substation
{
    gates:
        inout control_gate[];
        input power_gate_in[];
        output power_gate_out[];
}

simple Consumer
{
    gates:
        inout control_gate[];
        input power_gate_in[];
}

network Topology
{
    @display("bgb=595,418");
    types:
        channel PowerLine extends ned.DatarateChannel
        {
        }
        channel ControlLine extends ned.DatarateChannel
        {
            @display("ls=gray");
        }
    submodules:
        cc: ControlCenter {
            @display("i=smartgrid/control-center;p=307,98");
        }
        pp1: PowerPlant {
            @display("i=smartgrid/power-plant;p=90,157");
        }
        pp2: PowerPlant {
            @display("i=smartgrid/power-plant;p=90,281");
        }
        ss1: Substation {
            @display("i=smartgrid/transformer;p=226,218");
        }
        ss2: Substation {
            @display("i=smartgrid/transformer;p=379,218");
        }
        c1: Consumer {
            @display("i=smartgrid/home;p=512,157");
        }
        c2: Consumer {
            @display("i=smartgrid/home;p=512,218");
        }
        c3: Consumer {
            @display("i=smartgrid/home;p=512,281");
        }
    connections:
        cc.control_gate++ <--> ControlLine <--> pp1.control_gate++;
        cc.control_gate++ <--> ControlLine <--> pp2.control_gate++;
        cc.control_gate++ <--> ControlLine <--> ss1.control_gate++;
        cc.control_gate++ <--> ControlLine <--> ss2.control_gate++;
        cc.control_gate++ <--> ControlLine <--> c1.control_gate++;
        cc.control_gate++ <--> ControlLine <--> c2.control_gate++;
        cc.control_gate++ <--> ControlLine <--> c3.control_gate++;
        pp1.power_gate_out++ --> PowerLine --> ss1.power_gate_in++;
        pp2.power_gate_out++ --> PowerLine --> ss1.power_gate_in++;
        ss1.power_gate_out++ --> PowerLine --> ss2.power_gate_in++;
        ss2.power_gate_out++ --> PowerLine --> c1.power_gate_in++;
        ss2.power_gate_out++ --> PowerLine --> c2.power_gate_in++;
        ss2.power_gate_out++ --> PowerLine --> c3.power_gate_in++;
}
