using ChmcuInit.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace ChmcuInit.Service
{
    public class XMLFamilies : IXMLFamiliesData
    {
        public List<McuFeature> GetAllDishes()
        {
            List<McuFeature> dishLIst = new List<McuFeature>();
            string xmlFileName = System.IO.Path.Combine(Environment.CurrentDirectory, @"Data\Data.xml");
            XDocument xDoc = XDocument.Load(xmlFileName);
            var dishes = xDoc.Descendants("Dish");
            foreach (var d in dishes)
            {
                McuFeature dish = new McuFeature();
                dishLIst.Add(dish);
            }

            return dishLIst;
        }
    }
}
