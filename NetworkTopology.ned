import inet.applications.contract.IApp;
import inet.applications.tcpapp.TcpClientApp;
import inet.applications.tcpapp.TcpServerApp;
import inet.applications.tcpapp.TcpGenericServerApp;
import inet.applications.tcpapp.TcpBasicClientApp;
import inet.applications.tcpapp.TelnetApp;
import inet.applications.tcpapp.TelnetClientApp;
import inet.applications.tcpapp.TelnetServerApp;
import inet.applications.tcpapp.TcpServerHostApp;
import inet.applications.tcpapp.TcpEchoApp;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.ethernet.Eth100M;
import inet.node.ethernet.Eth10M;
import inet.node.ethernet.EtherLink;
import inet.node.ethernet.EtherSwitch;
import inet.node.inet.Router;
import inet.node.inet.StandardHost;
import inet.visualizer.integrated.IntegratedCanvasVisualizer;

simple ControlCenter
{
    parameters:
        volatile int power_plant_num;
        volatile int substation_num;
        volatile int consumer_num;
        volatile string power_plant_info;
    gates:
        inout control_gate[];
        inout power_gate[];
}

simple PowerPlant
{
    gates:
        inout control_gate[];
        inout power_gate[];
}

simple Substation
{
    parameters:
        volatile int power_gate_in;
        volatile int power_gate_out;
    gates:
        inout control_gate[];
        inout power_gate[];
}

simple Consumer
{
    gates:
        inout control_gate[];
        inout power_gate[];
}

module ControlCenterHost extends StandardHost
{
    gates:
        inout control_gate[];
        inout power_gate[];
}

module PowerPlantHost extends StandardHost
{
    gates:
        inout power_gate[];
}

module SubstationHost extends StandardHost
{
    gates:
        inout power_gate[];
}

module ConsumerHost extends StandardHost
{
    gates:
        inout power_gate[];
}

simple ControlCenterApp extends TcpGenericServerApp
{
}

module PowerPlantApp extends TcpBasicClientApp
{
}

module SubstationtApp extends TcpBasicClientApp
{
}

simple ConsumerApp extends TcpBasicClientApp
{
}

network NodeTopology
{
    @display("bgb=659,521");
    types:
        channel PowerLine extends ned.DatarateChannel
        {
        }
        channel ControlLine extends EtherLink
        {
            @display("ls=gray");
            datarate = 10Mbps;
        }
    submodules:
        configurator: Ipv4NetworkConfigurator {
   			@display("p=50,50");
        }
        cc: ControlCenter {
            @display("i=smartgrid/control-center;p=317,125");
        }
        pp[2]: PowerPlant {
            @display("i=smartgrid/power-plant;p=100,280,c,120");
        }
        ss[2]: Substation {
            @display("i=smartgrid/transformer;p=240,340,r,150");
        }
        c[3]: Consumer {
            @display("i=smartgrid/home;p=530,280,c,60");
        }
    connections:
        for i=0..2-1 {
            cc.control_gate++ <--> ControlLine <--> pp[i].control_gate++;
        }
        for i=0..2-1 {
            cc.control_gate++ <--> ControlLine <--> ss[i].control_gate++;
        }
        for i=0..3-1 {
            cc.control_gate++ <--> ControlLine <--> c[i].control_gate++;
        }
        for i=0..2-1 {
            pp[i].power_gate++ <--> PowerLine <--> ss[0].power_gate++;
        }
        ss[0].power_gate++ <--> PowerLine <--> ss[1].power_gate++;
        for i=0..3-1 {
            ss[1].power_gate++ <--> PowerLine <--> c[i].power_gate++;
        }    
}

network AppTopology
{
    @display("bgb=659,521");
    types:
        channel PowerLine extends ned.DatarateChannel
        {
        }
        channel ControlLine extends EtherLink
        {
            @display("ls=gray");
            datarate = 10Mbps;
        }
    submodules:
        configurator: Ipv4NetworkConfigurator {
   			@display("p=50,50");
        }
        cc: ControlCenterHost {
            @display("i=smartgrid/control-center;p=317,125");
        }
        pp[2]: PowerPlantHost {
            @display("i=smartgrid/power-plant;p=100,280,c,120");
        }
        ss[2]: SubstationHost {
            @display("i=smartgrid/transformer;p=240,340,r,150");
        }
        c[3]: ConsumerHost {
            @display("i=smartgrid/home;p=530,280,c,60");
        }
        sw: EtherSwitch {
            @display("p=316.05,202.65");
        }
    connections:
        cc.ethg++ <--> ControlLine <--> sw.ethg++;
        for i=0..2-1 {
            sw.ethg++ <--> ControlLine <--> pp[i].ethg++;
        }
        for i=0..2-1 {
            sw.ethg++ <--> ControlLine <--> ss[i].ethg++;
        }
        for i=0..3-1 {
            sw.ethg++ <--> ControlLine <--> c[i].ethg++;
        }
        for i=0..2-1 {
            pp[i].power_gate++ <--> PowerLine <--> ss[0].power_gate++;
        }
        ss[0].power_gate++ <--> PowerLine <--> ss[1].power_gate++;
        for i=0..3-1 {
            ss[1].power_gate++ <--> PowerLine <--> c[i].power_gate++;
        }
}
