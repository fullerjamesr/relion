#include "pdb_helper.h"

using namespace gravis;


std::map<std::string,std::vector<d3Vector>> PdbHelper::groupAtoms(
		const Assembly& assembly,
		bool byElement)
{
	std::map<std::string,std::vector<d3Vector>> out;
	
	const int mc = assembly.molecules.size();
	
	for (int m = 0; m < mc; m++)
	{
		const Molecule& molecule = assembly.molecules[m];
		
		const int rc = molecule.residues.size();
		
		for (int r = 0; r < rc; r++)
		{
			const Residue& residue = molecule.residues[r];
			
			const int ac = residue.atoms.size();
			
			for (int a = 0; a < ac; a++)
			{
				const Atom& atom = residue.atoms[a];
				const std::string key = byElement? getElement(atom.name) : atom.name;
				out[key].push_back(getPosition(atom));
			}
		}
	}
	
	const int lac = assembly.looseAtoms.size();
	
	for (int la = 0; la < lac; la++)
	{
		const Atom& atom = assembly.looseAtoms[la];
		out[getElement(atom.name)].push_back(getPosition(atom));
	}
	
	return out;
}

std::map<std::string, std::map<std::string, std::vector<d3Vector>>> 
	PdbHelper::groupAtomsByResidue(const Assembly &assembly)
{
	std::map<std::string, std::map<std::string, std::vector<d3Vector>>> out;
	
	const int mc = assembly.molecules.size();
	
	for (int m = 0; m < mc; m++)
	{
		const Molecule& molecule = assembly.molecules[m];
		
		const int rc = molecule.residues.size();
		
		for (int r = 0; r < rc; r++)
		{
			const Residue& residue = molecule.residues[r];
			
			const int ac = residue.atoms.size();
			
			for (int a = 0; a < ac; a++)
			{
				const Atom& atom = residue.atoms[a];
				out[residue.name][atom.name].push_back(getPosition(atom));
			}
		}
	}
	
	return out;
}

std::string PdbHelper::getElement(const std::string& atomName)
{
	if (atomName[0] == ' ') return atomName.substr(1, 1);
	else return atomName.substr(0, 2);
}

d3Vector PdbHelper::getPosition(const Atom &atom)
{
	const Matrix1D<RFLOAT>& c = atom.coords;
	
	return d3Vector(c(0), c(1), c(2));
}
