// Kovthanan …
#include<yade/lib/base/Math.hpp>
#include<yade/core/GlobalEngine.hpp>
#include<yade/pkg/common/Collider.hpp>


class SpheresFactory: public GlobalEngine {
	shared_ptr<Collider> collider;
	protected:
		// Pick random position of a sphere. Should be override in derived engine.
		virtual void pickRandomPosition(Vector3r&/*picked position*/, Real/*sphere's radius*/);
	public:
		virtual void action();
	DECLARE_LOGGER;
	YADE_CLASS_BASE_DOC_ATTRS(SpheresFactory,GlobalEngine,"Engine for spitting spheres based on mass flow rate, particle size distribution etc. Initial velocity of particles is given by *vMin*, *vMax*, the *massFlowRate* determines how many particles to generate at each step. When *goalMass* is attained or positive *maxParticles* is reached, the engine does not produce particles anymore. Geometry of the region should be defined in a derived engine by overridden SpheresFactory::pickRandomPosition(). \n\nA sample script for this engine is in :ysrc:`scripts/spheresFactory.py`.",
		((Real,massFlowRate,NaN,,"Mass flow rate [kg/s]"))
		((Real,rMin,NaN,,"Minimum radius of generated spheres (uniform distribution)"))
		((Real,rMax,NaN,,"Maximum radius of generated spheres (uniform distribution)"))
		((Real,vMin,NaN,,"Minimum velocity norm of generated spheres (uniform distribution)"))
		((Real,vMax,NaN,,"Maximum velocity norm of generated spheres (uniform distribution)"))
		((Real,vAngle,NaN,,"Maximum angle by which the initial sphere velocity deviates from the normal."))
		((Vector3r,normal,Vector3r(NaN,NaN,NaN),,"Spitting direction (and orientation of the region's geometry)."))
		((int,materialId,-1,,"Shared material id to use for newly created spheres (can be negative to count from the end)"))
		((int,mask,-1,,"groupMask to apply for newly created spheres "))
		((vector<int>,ids,,,"ids of created bodies"))
		((Real,totalMass,0,,"Mass of spheres that was produced so far. |yupdate|"))
		((Real,goalMass,0,,"Total mass that should be attained at the end of the current step. |yupdate|"))
		((int,maxParticles,100,,"The number of particles at which to stop generating new ones (regardless of massFlowRate"))
		((int,numParticles,0,,"Cummulative number of particles produces so far |yupdate|"))
		((int,maxAttempt,5000 ,,"Maximum number of attempts to position a new sphere randomly."))
		((bool,silent,false ,,"If true no complain about excessing maxAttempt but disable the factory (by set massFlowRate=0)."))
		((std::string,blockedDOFs,"" ,,"Blocked degress of freedom"))
	);
};
REGISTER_SERIALIZABLE(SpheresFactory);

class CircularFactory: public SpheresFactory {
	protected:
		virtual void pickRandomPosition(Vector3r&, Real);
	public:
		virtual ~CircularFactory(){};
		DECLARE_LOGGER;
		YADE_CLASS_BASE_DOC_ATTRS(CircularFactory,SpheresFactory,"Circular geometry of the SpheresFactory region. It can be disk (given by radius and center), or cylinder (given by radius, length and center).",
		((Real,radius,NaN,,"Radius of the region"))
		((Real,length,0,,"Length of the cylindrical region (0 by default)"))
		((Vector3r,center,Vector3r(NaN,NaN,NaN),,"Center of the region"))
	);
};
REGISTER_SERIALIZABLE(CircularFactory);

class BoxFactory: public SpheresFactory {
	protected:
		virtual void pickRandomPosition(Vector3r&, Real);
	public:
		virtual ~BoxFactory(){};
		DECLARE_LOGGER;
		YADE_CLASS_BASE_DOC_ATTRS(BoxFactory,SpheresFactory,"Box geometry of the SpheresFactory region, given by extents and center",
		((Vector3r,extents,Vector3r(NaN,NaN,NaN),,"Extents of the region"))
		((Vector3r,center,Vector3r(NaN,NaN,NaN),,"Center of the region"))
	);
};
REGISTER_SERIALIZABLE(BoxFactory);
