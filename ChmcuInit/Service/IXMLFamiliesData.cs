using ChmcuInit.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ChmcuInit.Service
{
    public interface IXMLFamiliesData
    {
        List<string>        GetAllCompanyName();
        List<string>        GetAllFamilyName(string CompanyName);
        List<string>        GetAllSubFamilyName(string CompanyName, string FamilyName);
        List<string>        GetAllMcuName(string CompanyName, string FamilyName, string SubFamilyName);
        McuFeature          GetAllMcuFeatures(string CompanyName, string FamilyName, string SubFamilyName, string McuName);
    }
}
