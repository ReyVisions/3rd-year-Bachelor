using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using System.Threading;
using System.Linq;

/// <summary>
/// Classe qui permet de déterminer toutes les
/// actions à faire lorsque l'agent est dans l'état
/// "Idle".
/// Lorsque l'agent est dans cet état, il ne bouge
/// plus et est dans l'attente d'une nouvelle
/// action à réaliser.
/// 
/// Fait par EL MONTASER Osmane le 17/04/2022. 
/// /// Modifie par Remy XU le 03/04/2023
/// </summary>
public class BreedAgentAction : AgentAction {

    private GameObject _child;

    private GameObject _mate;

    private Vector3 oldLocalScale;

    /// <summary>
    /// Permet d'initialiser l'attribut _agent.
    /// </summary>
    /// <param name="agent">
    /// L'agent sur lequel l'action est réalisée.
    /// </param>
    public BreedAgentAction(Agent agent) : base(agent) { }


    /// <summary>
    /// Dans cet fonction, il est fait en sorte que 
    /// l'agent cherche de la nourriture en fonction de
    /// son régime alimentaire.
    /// 
    /// Fait par EL MONTASER Osmane le 17/04/2022.
    /// Modifie par Remy XU le 03/03/2023-03/04/2023
    /// </summary>
    public override void update() {
        if (!_agent.Attributes["SpeciesName"].Equals("Grass"))
        {
            if (_agent.GetComponent<UnityEngine.AI.NavMeshAgent>().enabled == true)
            {
                _agent.AgentMesh.isStopped = false;
            }
            //_agent.GetComponent<UnityEngine.AI.NavMeshAgent>().enabled = true;
        }
        
        breed();
        //Gestion de l'endurence lors du sprint
        //Gestion de l'endurence lors du sprint
        if (ManualControl.isSprinting == true)
        {
            _agent.Attributes["Stamina"] = (Convert.ToDouble(_agent.Attributes["Stamina"]) - 3 * (Time.deltaTime * (ActionNames.TimeSpeed / ActionNames.DAY_DURATION) * ActionNames.STAMINA_FACTOR) * GameObject.Find("Terrain").GetComponent<SeasonManager>().statusConsumption("Stamina")).ToString();
        }
        else
        {
            _agent.Attributes["Stamina"] = (Convert.ToDouble(_agent.Attributes["Stamina"]) - (Time.deltaTime * (ActionNames.TimeSpeed / ActionNames.DAY_DURATION) * ActionNames.STAMINA_FACTOR) * GameObject.Find("Terrain").GetComponent<SeasonManager>().statusConsumption("Stamina")).ToString();
        }
        _agent.Attributes["EnergyNeeds"] = (Convert.ToDouble(_agent.Attributes["EnergyNeeds"]) + (Time.deltaTime * (ActionNames.TimeSpeed / ActionNames.DAY_DURATION) * ActionNames.ENERGY_FACTOR) * GameObject.Find("Terrain").GetComponent<SeasonManager>().statusConsumption("EnergyNeeds")).ToString();
        _agent.Attributes["WaterNeeds"] = (Convert.ToDouble(_agent.Attributes["WaterNeeds"]) + (Time.deltaTime * (ActionNames.TimeSpeed / ActionNames.DAY_DURATION) * ActionNames.WATER_FACTOR) * GameObject.Find("Terrain").GetComponent<SeasonManager>().statusConsumption("WaterNeeds")).ToString();
        //throw new NotImplementedException();
        if (_agent.PredateursVisible() == true)
            _agent.Attributes["Fear"] = (Convert.ToDouble(_agent.Attributes["Fear"]) + (Time.deltaTime * (ActionNames.TimeSpeed / ActionNames.DAY_DURATION) * ActionNames.FEAR_FACTOR * 2000)).ToString();
        else
            _agent.Attributes["Fear"] = (Convert.ToDouble(_agent.Attributes["Fear"]) - (Time.deltaTime * (ActionNames.TimeSpeed / ActionNames.DAY_DURATION) * ActionNames.FEAR_FACTOR) * 400).ToString();
        if (Convert.ToDouble(_agent.Attributes["Fear"]) < 0)
        {
            _agent.Attributes["Fear"] = 0.ToString();
        }
        if (Convert.ToDouble(_agent.Attributes["Fear"]) > 1)
        {
            _agent.Attributes["Fear"] = 1.ToString();
        }
        if (Convert.ToDouble(_agent.Attributes["Stamina"]) < 0)
        {
            _agent.Attributes["Stamina"] = 0.ToString();
        }
        if (bool.Parse(_agent.Attributes["IsAlive"]))
            _agent.Attributes["Health"] = (Convert.ToDouble(_agent.Attributes["Health"]) + (Time.deltaTime * (ActionNames.TimeSpeed / ActionNames.DAY_DURATION) * ActionNames.HEALING_FACTOR)).ToString();
        if ((Convert.ToDouble(_agent.Attributes["Health"]) > (Convert.ToDouble(_agent.Attributes["MaxHealth"]))))
        {
            _agent.Attributes["Health"] = _agent.Attributes["MaxHealth"];
        }
    }

    /// <summary>
    /// Permet aux agents de se reproduire.
    /// Les agents autotrophes se reproduisent tout seuls,
    /// tandis que les autres agents ont besoin d'un partenaire.
    ///
    /// Fait par EL MONTASER Osmane le 28/04/2022.
    /// Modifie par Remy XU le 03/03/2023
    /// Modifier par ROSSIGNOL PAUL le 17/03/2023
    /// 
    /// </summary> 
    private void breed() {
        if(_agent.Attributes["SpeciesName"].Equals("Grass") && _child == null) {
            System.Random rnd = new System.Random();
            float randomX = rnd.Next((int)_agent.transform.position.x - 5, (int)_agent.transform.position.x + 5);
            float randomY = rnd.Next((int)_agent.transform.position.z - 5, (int)_agent.transform.position.z + 5);
            GameObject go = GameObject.Instantiate(GameObject.Find("AgentManager").GetComponent<AgentManager>().Grass, 
                new Vector3(randomX, Terrain.activeTerrain.SampleHeight(new Vector3(randomX, 1f, randomY)),randomY), Quaternion.identity);
            go.name = "Grass";
            oldLocalScale = go.transform.localScale;
            go.transform.localScale = new Vector3(0, 0, 0);
            _child = go;
        } else if(!_agent.Attributes["SpeciesName"].Equals("Grass")) {
            _mate = _agent.GetMate();
            
            if (_mate == null)
            {
                findMate(_agent);
                if(_mate != null)
                {
                    _agent.EndBreed = false;
                    _mate.GetComponent<Agent>().EndBreed = false;
                }
               
            }
                  

            
            else if(_mate != null && _agent.GetComponent<UnityEngine.AI.NavMeshAgent>().enabled == true && !_agent.Attributes["SpeciesName"].Equals("Grass")) {
                
                _agent.AgentMesh.SetDestination(_mate.GetComponent<Agent>().transform.position);
              
                if((_agent.AgentMesh.remainingDistance <= 2.0f)) {

                    if (_agent.Attributes["Gender"].Equals("2"))
                    {
                     
                        _agent.Attributes["IsPregnant"] = "true";
                        _mate.GetComponent<Agent>().Attributes["EnergyNeeds"] = _agent.Attributes["SpeciesName"].Equals("Grass") ? "1.0" : "0.5";
                        _mate.GetComponent<Agent>().Attributes["Stamina"] = _agent.Attributes["SpeciesName"].Equals("Grass") ? "1.0" : "0.38";
                        _agent.Attributes["EnergyNeeds"] = _agent.Attributes["SpeciesName"].Equals("Grass") ? "1.0" : "0.5";
                        _agent.Attributes["Stamina"] = _agent.Attributes["SpeciesName"].Equals("Grass") ? "1.0" : "0.38";

                        if (bool.Parse(_agent.Attributes["CanHavePack"]))
                        {
                            if (_agent.getCurrentPackType() == TypeAgentForPack.WithoutPack && _mate.GetComponent<Agent>().getCurrentPackType() == TypeAgentForPack.WithoutPack)
                                _agent.createPack(_mate);
                            else if (_agent.getCurrentPackType() == TypeAgentForPack.WithPack && _mate.GetComponent<Agent>().getCurrentPackType() == TypeAgentForPack.WithoutPack)
                            {
                                _agent.AddAgentToPack(_mate);

                            }
                            else if (_mate.GetComponent<Agent>().getCurrentPackType() == TypeAgentForPack.WithPack && _agent.getCurrentPackType() == TypeAgentForPack.WithoutPack)
                            {
                                _mate.GetComponent<Agent>().AddAgentToPack(_agent.gameObject);
                            }
                        }
                    }
                    else if(_mate.GetComponent<Agent>().Attributes["Gender"].Equals("2")){
                        _mate.GetComponent<Agent>().Attributes["IsPregnant"] = "true";
                        _agent.Attributes["EnergyNeeds"] = _agent.Attributes["SpeciesName"].Equals("Grass") ? "1.0" : "0.5";
                        _agent.Attributes["Stamina"] = _agent.Attributes["SpeciesName"].Equals("Grass") ? "1.0" : "0.38";
                        _mate.GetComponent<Agent>().Attributes["EnergyNeeds"] = _agent.Attributes["SpeciesName"].Equals("Grass") ? "1.0" : "0.5";
                        _mate.GetComponent<Agent>().Attributes["Stamina"] = _agent.Attributes["SpeciesName"].Equals("Grass") ? "1.0" : "0.38";
                        if (bool.Parse(_agent.Attributes["CanHavePack"]))
                        {

                            if (_agent.ListC[0] == Agentcharacteristics.Sociable && _mate.GetComponent<Agent>().ListC[0] == Agentcharacteristics.Sociable)
                            {
                                if (_agent.getCurrentPackType() == TypeAgentForPack.WithoutPack && _mate.GetComponent<Agent>().getCurrentPackType() == TypeAgentForPack.WithoutPack)
                                    _agent.createPack(_mate);
                                else if (_agent.getCurrentPackType() == TypeAgentForPack.WithPack && _mate.GetComponent<Agent>().getCurrentPackType() == TypeAgentForPack.WithoutPack)
                                {
                                    _agent.AddAgentToPack(_mate);

                                }
                                else if (_mate.GetComponent<Agent>().getCurrentPackType() == TypeAgentForPack.WithPack && _agent.getCurrentPackType() == TypeAgentForPack.WithoutPack)
                                {
                                    _mate.GetComponent<Agent>().AddAgentToPack(_agent.gameObject);
                                }
                            }
                           
                        }
                    }


                    _agent.EndBreed = true;
                    _mate.GetComponent<Agent>().EndBreed = true;
                    _mate = null;
                }
            }
           
        } 
        if(_child != null) {
            Agent child;
            if((_child.name.Equals("Rabbit") && new System.Random().NextDouble() > 0.25)
                || (!_child.name.Equals("Rabbit") && new System.Random().NextDouble() > 0.6)) {
                child = _child.GetComponent<Agent>();
                _child.transform.localScale = oldLocalScale;
                child.initialisation();
                string name = child.Attributes["SpeciesName"].Split('(')[0];
                child.Attributes["EnergyNeeds"] = _agent.Attributes["SpeciesName"].Equals("Grass") ? "1.0" : "0.0";
                GameObject.Find("Player").GetComponent<DataUpdater>().AddNewAgent(child);
            } else {
                GameObject.Destroy(_child);
            }
            
            _agent.Attributes["EnergyNeeds"] = _agent.Attributes["SpeciesName"].Equals("Grass") ? "1.0" : _agent.Attributes["EnergyNeeds"];
            _agent.Attributes["Stamina"] = _agent.Attributes["SpeciesName"].Equals("Grass") ? "1.0" : "0.38";
            _child = null;
        }
    }
    /// <summary>
    /// Traitement du cas du mode contrôle manuel
    /// Modifier par Rossinol Paul le 17/03/2023
    /// Modifie par Remy Xu le 22/03/2023
    /// </summary>
    bool GetAMate;
    private void findMate(Agent agent) {
        
        if (!_agent.Attributes["SpeciesName"].Equals("Grass") 
            && (_agent.AgentMesh != null) 
            && (!_agent.AgentMesh.pathPending)
            && _agent.GetComponent<UnityEngine.AI.NavMeshAgent>().enabled == true) { //Desactive les fonctions utilisant la Navmesh si on est en mode manuel
            _agent.walker();
        }
        IEnumerable<GameObject> possibleMates = from candidate in _agent.animauxDansFov()
                            where (candidate.GetComponent<Agent>().Attributes["SpeciesName"].Equals(_agent.Attributes["SpeciesName"]) 
                            && (candidate.GetComponent<Agent>().Attributes["Gender"].Equals("2") ^ _agent.Attributes["Gender"].Equals("2")) 
                            && (candidate.GetComponent<Agent>().Attributes["IsAlive"].Equals("true") 
                            && (candidate.GetComponent<Agent>().Attributes["IsPregnant"]).Equals("false")))
                            select candidate;
        
        if (possibleMates.Count() != 0) {
            foreach (GameObject ob in possibleMates)
            {  
                if (ob.GetComponent<Agent>().Attributes["Gender"].Equals("2") ^ _agent.Attributes["Gender"].Equals("2"))
                {
                    if (canHaveReproduction(_agent, ob.GetComponent<Agent>()))
                    {
                        ob.GetComponent<Agent>().SetMate(_agent.gameObject);
                        _agent.SetMate(ob);
                    }
                } 
            }
        }
          
        
        else if(_agent.GetMate() == null && _agent.GetComponent<UnityEngine.AI.NavMeshAgent>().enabled == true) //Desactive les fonctions utilisant la Navmesh si on est en mode manuel
        {

                _agent.walker();
        }
        
    }

    /// <summary>
    /// Savoir si l'agent en question est en capacité
    /// de se reproduire. Cela afin d'éviter que des
    /// animaux enceintes ne se reproduisent ainsi
    /// que les animaux n'ayant pas la majorité
    /// sexuelle.
    /// La monogamie est activée par défaut.
    /// 
    /// Fait par EL MONTASER Osmane le 06/05/2022.
    /// </summary>
    /// <param name="agent">
    /// 
    /// </param>
    /// <returns></returns>
    private bool isBreedingReady(Agent agent) {
        return false;
    }

    /// <summary>
    /// Fait par ROSSIGNOL PAUL le 26/03/2023
    /// </summary>
    /// <param name="a"></param>
    /// <param name="b"></param>
    /// <returns></returns>
    /// 
    public Boolean canHaveReproduction(Agent a, Agent b)
    {
        if (b.getCurrentPackType() == TypeAgentForPack.WithPack && a.getCurrentPackType() == TypeAgentForPack.Alpha)
        {
            if (b.Packs.Contains(a.gameObject) && a.Packs.Contains(b.gameObject))
            {
                return true;
            }
            else return false;


        }
        else return true;
    }
}