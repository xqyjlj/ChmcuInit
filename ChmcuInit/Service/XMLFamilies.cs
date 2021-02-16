using ChmcuInit.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using System.Xml.Linq;

namespace ChmcuInit.Service
{
    public class XMLFamilies : IXMLFamiliesData
    {
        public List<string> GetAllCompanyName()
        {
            List<string> list = new List<string>();
            XmlDocument xmlDoc = new XmlDocument();
            XmlReaderSettings settings = new XmlReaderSettings();
            settings.IgnoreComments = true;
            XmlReader reader = XmlReader.Create(@"Data/families.xml", settings);
            xmlDoc.Load(reader);
            string node = (@"Families/Company");
            foreach (XmlElement book in xmlDoc.SelectNodes(node))
            {
                list.Add(book.GetAttribute(@"Name"));
            }
            return list;
        }

        public List<string> GetAllFamilyName(string CompanyName)
        {
            List<string> list = new List<string>();
            XmlDocument xmlDoc = new XmlDocument();
            XmlReaderSettings settings = new XmlReaderSettings();
            settings.IgnoreComments = true;
            XmlReader reader = XmlReader.Create(@"Data/families.xml", settings);
            xmlDoc.Load(reader);
            string node = (@"Families/Company[@Name='") +
                CompanyName + (@"']/Family");
            foreach (XmlElement book in xmlDoc.SelectNodes(node))
            {
                Console.WriteLine("id value: {0}.", book.GetAttribute("Name"));
                list.Add(book.GetAttribute("Name"));
            }
            return list;
        }

        public List<string> GetAllSubFamilyName(string CompanyName, string FamilyName)
        {
            List<string> list = new List<string>();
            XmlDocument xmlDoc = new XmlDocument();
            XmlReaderSettings settings = new XmlReaderSettings();
            settings.IgnoreComments = true;
            XmlReader reader = XmlReader.Create(@"Data/families.xml", settings);
            xmlDoc.Load(reader);
            string node = (@"Families/Company[@Name='") +
                CompanyName + (@"']/Family[@Name='") +
                FamilyName + (@"']/SubFamily");
            foreach (XmlElement book in xmlDoc.SelectNodes(node))
            {
                Console.WriteLine("id value: {0}.", book.GetAttribute("Name"));
                list.Add(book.GetAttribute("Name"));
            }
            return list;
        }

        public List<string> GetAllMcuName(string CompanyName, string FamilyName, string SubFamilyName)
        {
            List<string> list = new List<string>();
            XmlDocument xmlDoc = new XmlDocument();
            XmlReaderSettings settings = new XmlReaderSettings();
            settings.IgnoreComments = true;
            XmlReader reader = XmlReader.Create(@"Data/families.xml", settings);
            xmlDoc.Load(reader);
            string node = (@"Families/Company[@Name='") +
                CompanyName + (@"']/Family[@Name='") +
                FamilyName + (@"']/SubFamily[@Name='") +
                SubFamilyName + (@"']/Mcu");
            foreach (XmlElement book in xmlDoc.SelectNodes(node))
            {
                Console.WriteLine("id value: {0}.", book.GetAttribute("Name"));
                list.Add(book.GetAttribute("Name"));
            }
            return list;
        }

        public McuFeature GetAllMcuFeatures(string CompanyName, string FamilyName, string SubFamilyName, string McuName)
        {
            List<McuFeaturePeripheral> mcuFeaturePeripherals = new List<McuFeaturePeripheral>();
            McuFeature mcuFeature = new McuFeature();
            XmlDocument xmlDoc = new XmlDocument();
            XmlReaderSettings settings = new XmlReaderSettings();
            settings.IgnoreComments = true;
            XmlReader reader = XmlReader.Create(@"Data/families.xml", settings);
            xmlDoc.Load(reader);
            string node = (@"Families/Company[@Name='") +
                CompanyName + (@"']/Family[@Name='") +
                FamilyName + (@"']/SubFamily[@Name='") +
                SubFamilyName + (@"']/Mcu[@Name='" +
                McuName + @"']");
            foreach (XmlElement book in xmlDoc.SelectNodes(node))
            {
                mcuFeature.McuPackageName = book.GetAttribute("PackageName");
                for (int i = 0; i < book.ChildNodes.Count; i++)
                {
                    XmlNode xmlNode = book.ChildNodes[i];
                    if (xmlNode.Name == (@"Core"))
                    {
                        mcuFeature.Core = xmlNode.InnerText;
                    }
                    else if (xmlNode.Name == (@"Frequency"))
                    {
                        mcuFeature.Frequency = xmlNode.InnerText;
                    }
                    else if (xmlNode.Name == (@"Ram"))
                    {
                        mcuFeature.Ram = xmlNode.InnerText;
                    }
                    else if (xmlNode.Name == (@"IO"))
                    {
                        mcuFeature.IO = xmlNode.InnerText;
                    }
                    else if (xmlNode.Name == (@"Flash"))
                    {
                        mcuFeature.Flash = xmlNode.InnerText;
                    }
                    else if (xmlNode.Name == (@"Voltage"))
                    {
                        McuFeatureVoltage mcuFeatureVoltage = new McuFeatureVoltage();
                        foreach (XmlAttribute attribute in xmlNode.Attributes)
                        {                       
                            if (attribute.Name == "Min")
                            {
                                mcuFeatureVoltage.Min = attribute.Value.ToString();
                            }
                            else if(attribute.Name == "Max")
                            {
                                mcuFeatureVoltage.Max = attribute.Value.ToString();
                            }
                        }
                        mcuFeature.Voltage = mcuFeatureVoltage;
                    }
                    else if (xmlNode.Name == (@"Current"))
                    {
                        McuFeatureCurrent mcuFeatureCurrent = new McuFeatureCurrent();
                        foreach (XmlAttribute attribute in xmlNode.Attributes)
                        {
                            if (attribute.Name == "Lowest")
                            {
                                mcuFeatureCurrent.Lowest = attribute.Value.ToString();
                            }
                            else if (attribute.Name == "Run")
                            {
                                mcuFeatureCurrent.Run = attribute.Value.ToString();
                            }
                        }
                        mcuFeature.Current = mcuFeatureCurrent;
                    }
                    else if (xmlNode.Name == (@"Temperature"))
                    {
                        McuFeatureTemperature mcuFeatureTemperature = new McuFeatureTemperature();
                        foreach (XmlAttribute attribute in xmlNode.Attributes)
                        {
                            if (attribute.Name == "Min")
                            {
                                mcuFeatureTemperature.Min = attribute.Value.ToString();
                            }
                            else if (attribute.Name == "Max")
                            {
                                mcuFeatureTemperature.Max = attribute.Value.ToString();
                            }
                        }
                        mcuFeature.Temperature = mcuFeatureTemperature;
                    }
                    else if (xmlNode.Name == (@"Peripheral"))
                    {
                        McuFeaturePeripheral mcuFeaturePeripheral = new McuFeaturePeripheral();
                        foreach (XmlAttribute attribute in xmlNode.Attributes)
                        {
                            if (attribute.Name == "Type")
                            {
                                mcuFeaturePeripheral.Type = attribute.Value.ToString();
                            }
                            else if (attribute.Name == "Num")
                            {
                                mcuFeaturePeripheral.Num = attribute.Value.ToString();
                            }
                        }
                        mcuFeaturePeripherals.Add(mcuFeaturePeripheral);   
                    }
                }
            }
            mcuFeature.Peripheral = mcuFeaturePeripherals;
            return mcuFeature;
        }
    }
}
