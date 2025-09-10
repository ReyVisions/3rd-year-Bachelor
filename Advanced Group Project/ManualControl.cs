using System.Collections;
using System.Collections.Generic;
using System;
using UnityEngine;
using UnityEngine.AI;
using UnityEngine.UI;

/// <summary>
/// Classe pour le contrôle manuel de l'agent.
/// Fait par Remy XU le 12/03/2023
/// </summary>

public class ManualControl : MonoBehaviour
{
    /// <summary>
    /// Ensemble des variables pour le contrôle de l'agent.
    /// Fait par Remy XU le 12/03/2023
    /// </summary>
    [SerializeField] private Transform groundCheckTransform = null;

    public static bool grounded;
    private bool controlCondition;
    private Vector3 horizontalInput;
    private Vector3 verticalInput;

    /// <summary>
    /// Variables concernant la gravité appliquee 23/03/2023
    /// 29/03/2023 : Gravité pas idéale (cf OnTriggerEnter), on applique juste une grande velocité en y pour que l'agent tombe.
    /// </summary>
    private Rigidbody rigidbodyComponent;
    private float gravityValue = -9.81f;
    private float gravityMultiplier = 120.0f;
    [SerializeField] private float y_velocity;
    private float jumpHeight = 60;
    /// <summary>
    /// Variables pour la rotation de la capsule
    /// Fait par Remy XU le 14/03/2023
    /// </summary>
    private Vector3 rotation;
    [SerializeField] private float rotationSpeed = 75;


    private float agentSpeed;
    private float agentSpeedSprint; //variable stockant la vitesse de l'agent une fois après avoir appuye sur LeftControl.
    public static bool isSprinting;


    /// <summary>
    /// Variables pour récuperer le toggle.
    /// Fait par Remy XU le 14/03/2023
    /// </summary>
    public GameObject TogglerAgent;
    private Agent trackedAgent; //variable contenant l'agent traqué lorsqu'on clique dessus.
    private bool boolTogglerAgent;

    /// <summary>
    /// variable pour acceder aux axes de la camera de l'agent que l'on contrôle
    /// </summary>
    private GameObject camera;
    private Vector3 nullVector;

    /// <summary>
    /// Variable pour désactiver le contrôle manuel lorsque l'on dort manuellement
    /// 12/04/2023
    /// </summary>
    [SerializeField] private GameObject SleepToggler;

    /// <summary>
    /// Variable pour le mode nage manuelle.
    /// 13/04/2023
    /// </summary>
    public static bool swimModeOn;

    void Start()
    {
        nullVector = new Vector3(0, gravityValue * gravityMultiplier * Time.deltaTime, 0);
        TogglerAgent = FindChildGameObjectByName(GameObject.Find("Canvas"), "ManualControlToggle");
        swimModeOn = false;
    }

    /// <summary>
    /// Contrôle basique de l'agent + prendre en compte la case cochée du contrôle manuel
    /// Fait par Remy XU le 12/03/2023-13/04/2023
    ///
    /// </summary>
    void Update()
    {

        TogglerAgent = FindChildGameObjectByName(GameObject.Find("Canvas"), "ManualControlToggle");
        boolTogglerAgent = TogglerAgent.GetComponent<Toggle>().isOn;
        trackedAgent = GameObject.Find("AgentManager").GetComponent<AgentStatsGUIUpdater>().AgentToTrack;
        agentSpeed = relativeAgentSpeed(trackedAgent);
        if (trackedAgent != null && !trackedAgent.Attributes["SpeciesName"].Equals("Grass") && !SleepToggler.GetComponent<UnityEngine.UI.Toggle>().isOn&&trackedAgent.Attributes["IsAlive"] == "true")
        {
            if (boolTogglerAgent) //cas contrôle manuel coché
            {
                ApplyGravity();
                isSprinting = false;
                rigidbodyComponent = trackedAgent.GetComponent<Rigidbody>();
                trackedAgent.GetComponent<UnityEngine.AI.NavMeshAgent>().enabled = false;       //desactive le NavMeshAgent
                controlCondition = Input.GetKey(KeyCode.UpArrow) || Input.GetKey(KeyCode.DownArrow);
                //Variable qui permet de controler la capsule seulement avec ces touches là
                if (controlCondition)
                {
                    /// <summary>
                    /// Contrôle relatif à la camera
                    /// Remy XU 22/03/2023
                    /// </summary>
                    camera = FindChildGameObjectByName(GameObject.Find("Player"), "Main Camera");
                    horizontalInput = Input.GetAxis("Vertical") * camera.transform.forward;
                    verticalInput = Input.GetAxis("Vertical") * camera.transform.forward;
                }
                //Gestion du sprint en fonction de si on nage ou pas
                if (trackedAgent.getIsSwimming())
                {
                    //ManualSwimMode();

                    if (Input.GetKey(KeyCode.LeftControl))
                    {
                        agentSpeedSprint = Convert.ToSingle(1.5) * agentSpeed;
                        if (controlCondition) //Consomme 3x plus rapidement seulement si on bouge l'agent.
                        {
                            isSprinting = true;
                        }
                    }
                    else
                    {
                        agentSpeedSprint = agentSpeed;
                    }
                }
                else
                {
                    if (Input.GetKey(KeyCode.LeftControl))
                    {
                        agentSpeedSprint = 2 * agentSpeed;
                        //isSprinting=true; //Décommenter pour test: pour montrer facilement que l'endurence se consume bien 3x plus rapidement
                        if (controlCondition) //Consomme 3x plus rapidement seulement si on bouge l'agent.
                        {
                            isSprinting = true;
                        }
                    }
                    else
                    {
                        agentSpeedSprint = agentSpeed;
                    }
                }
            }
            else
            {
                trackedAgent.GetComponent<UnityEngine.AI.NavMeshAgent>().enabled = true;
                if (!trackedAgent.getIsSwimming())
                {
                    //trackedAgent.GetComponent<UnityEngine.AI.NavMeshAgent>().enabled = true;
                    y_velocity = 0;
                }
                else
                {
                    //trackedAgent.GetComponent<UnityEngine.AI.NavMeshAgent>().enabled = false;
                }
            }
        }
        else if(trackedAgent != null&&trackedAgent.Attributes["IsAlive"] == "false")
        {
            rigidbodyComponent.velocity = new Vector3(0, y_velocity, 0);
        }
    }
    //FixedUpdate is called once every physic update
    //Gestion du saut de l'agent
    private void FixedUpdate()
    {
        if (trackedAgent != null && !trackedAgent.Attributes["SpeciesName"].Equals("Grass") && !SleepToggler.GetComponent<UnityEngine.UI.Toggle>().isOn && trackedAgent.Attributes["IsAlive"] == "true")
        {

            if (boolTogglerAgent)
            {
                groundCheckTransform = trackedAgent.GetComponent<Transform>();
                rigidbodyComponent.velocity = nullVector;
                if (Input.GetKey(KeyCode.RightArrow))
                {
                    rotation = Vector3.up;
                    trackedAgent.transform.Rotate(rotation * rotationSpeed * Time.deltaTime);
                }
                if (Input.GetKey(KeyCode.LeftArrow))
                {
                    rotation = Vector3.down;
                    trackedAgent.transform.Rotate(rotation * rotationSpeed * Time.deltaTime);
                }
                if (controlCondition)
                {
                    /// <summary>
                    /// variable pour acceder aux axes de la camera de l'agent que l'on contrôle
                    /// </summary>
                    Vector3 moveDir = horizontalInput + verticalInput;
                    ApplyGravity();
                    //agentSpeed = int(trackedAgent.Attributes["Speed"]);

                    rigidbodyComponent.velocity = new Vector3(moveDir.x * agentSpeedSprint, y_velocity, moveDir.z * agentSpeedSprint);
                }
                if (Input.GetKeyDown(KeyCode.J) && grounded)
                {
                    rigidbodyComponent.AddForce(Vector3.up* jumpHeight, ForceMode.VelocityChange);
                }
            }
        }
    }
    /// <summary>
    /// Méthode appliquant moins de velocité sur les y lorsque l'on est au sol pour pas ralentir les mouvements
    /// ni ajouter des forces inutiles, mais applique la gravité lorsqu'on est en l'air.
    /// +Forces lors de la nage manuelle
    /// Fait par Remy Xu le 23/03/2023 et modification le 13/04/2023
    /// </summary>
    private void ApplyGravity()
    {
        rigidbodyComponent = trackedAgent.GetComponent<Rigidbody>();

        if (grounded)
        {
            y_velocity = -1.0f;
            //print("Au sol");
        }
        else if (trackedAgent.getIsSwimming())
        {

            trackedAgent.GetComponent<UnityEngine.AI.NavMeshAgent>().enabled = false;
            if (trackedAgent.transform.position.y < 22.5)
            {
                y_velocity = 4.0f;
                rigidbodyComponent.velocity = new Vector3(0, y_velocity, 0);
            }
            else
            {
                y_velocity = 0f;
                rigidbodyComponent.velocity = new Vector3(0, y_velocity, 0);
            }
        }else
        {
            //print("En l'air");
            y_velocity = gravityValue * gravityMultiplier * Time.deltaTime;
        }
        rigidbodyComponent.velocity = new Vector3(0, gravityValue * gravityMultiplier * Time.deltaTime, 0);
    }
    /// <summary>
    /// Pour tester si le toggle renvoie true lorsqu'il est coché et false sinon
    /// (Il faut mettre cette méthode en OnValueChanged de ManualControl Toggle et le choisir en boolDynamique)
    ///
    /// Fait par Remy XU le 14/03/2023
    /// </summary>  
    public void SwitchToManualControlToggle(bool tog)
    {
        print(tog);
    }

    /// <summary>
    /// Cherche le gameObject par le nom en récursif parmi tous les enfants à différents degrés du gameObject.
    /// 
    /// Fait par Remy XU le 15/03/2023
    /// </summary> 
    public static GameObject FindChildGameObjectByName(GameObject rootParentGameObject, string gameObjectName)
    {
        for (int i = 0; i < rootParentGameObject.transform.childCount; i++)
        {
            if (rootParentGameObject.transform.GetChild(i).name.ToLower() == gameObjectName.ToLower())
            {
                return (rootParentGameObject.transform.GetChild(i).gameObject);
            }
            GameObject tmp = FindChildGameObjectByName(rootParentGameObject.transform.GetChild(i).gameObject, gameObjectName);

            if (tmp != null)
            {
                return tmp;
            }
        }
        return (null);
    }
    /// <summary>
    /// Retourne une valeur de vitesse différente en fonction de la vitesse de l'agent.
    /// 
    /// Fait par Remy XU le 03/04/2023
    /// </summary> 
    public float relativeAgentSpeed(Agent agent)
    {
        if (trackedAgent.Attributes["SpeciesName"].Equals("Panda"))
        {
            return (3f);
        }
        else
        {
            return(Convert.ToSingle(1.5) * Convert.ToSingle(agent.Attributes["Speed"]));
        }
    }
    /*
    public void ManualSwimMode()
    {
        if (Input.GetKeyDown(KeyCode.N))
        {
            swimModeOn = !swimModeOn;
            camera = FindChildGameObjectByName(GameObject.Find("Player"), "Main Camera");
            horizontalInput = Input.GetAxis("Vertical") * camera.transform.forward;
            verticalInput = Input.GetAxis("Vertical") * camera.transform.forward;
            Vector3 moveDir = horizontalInput + verticalInput;
            rigidbodyComponent.velocity = new Vector3(moveDir.x * agentSpeedSprint, moveDir.y * agentSpeedSprint, moveDir.z * agentSpeedSprint);
        }
    }*/
}
