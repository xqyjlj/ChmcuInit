using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ChmcuInit.Models
{
    public class McuFeatureVoltage
    {
        public string                           Min                     { get; set; }
        public string                           Max                     { get; set; }
    }
    public class McuFeatureCurrent
    {
        public string                           Min                     { get; set; }
        public string                           Max                     { get; set; }
    }
    public class McuFeatureTemperature
    {
        public string                           Min                     { get; set; }
        public string                           Max                     { get; set; }
    }
    public class McuFeaturePeripheral
    {
        public string                           Type                    { get; set; }
        public string                           Num                     { get; set; }
    }
    public class McuFeature
    {
        public string                           McuName                 { get; set; }     
        public string                           McuPackageName          { get; set; }
        public string                           Core                    { get; set; }
        public string                           Frequency               { get; set; }
        public string                           Ram                     { get; set; }
        public string                           IO                      { get; set; }
        public string                           Flash                   { get; set; }
        public McuFeatureVoltage                Voltage                 { get; set; }
        public McuFeatureCurrent                Current                 { get; set; }
        public McuFeatureTemperature            Temperature             { get; set; }
        public List<McuFeaturePeripheral>       Peripheral              { get; set; }
    }
}
