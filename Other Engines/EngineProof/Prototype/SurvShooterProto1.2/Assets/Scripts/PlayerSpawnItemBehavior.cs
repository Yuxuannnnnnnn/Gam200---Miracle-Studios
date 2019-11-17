using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PlayerSpawnItemBehavior : MonoBehaviour
{
    public GameObject spawn;
    public Text CurrItem;
    public List<GameObject> Spawnables;

    int ItemCode;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Alpha1))
        {
            ItemCode = 0;
            CurrItem.text = "Current Item: Wall";
        }
        else if (Input.GetKeyDown(KeyCode.Alpha2))
        {
            ItemCode = 1;
            CurrItem.text = "Current Item: Turret";
        }

        if (Input.GetKeyDown(KeyCode.Space))
        {
            Instantiate(Spawnables[ItemCode],spawn.transform.position, spawn.transform.rotation);
        }
    }
}
