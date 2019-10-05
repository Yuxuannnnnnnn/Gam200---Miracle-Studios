using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RocketCollisionBehavior : MonoBehaviour
{
    public GameObject Explosion;
    SoundController sound;

    // Start is called before the first frame update
    void Start()
    {
        sound = GameObject.Find("SoundController").GetComponent<SoundController>();
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    void OnCollisionEnter2D(Collision2D coll)
    {
        if (coll.gameObject.tag == "Enemy")
        {
            Instantiate(Explosion,transform.position,transform.rotation);
            sound.PlaySound(sound.SFXList[2]);
        }
        Destroy(gameObject);
    }
}
