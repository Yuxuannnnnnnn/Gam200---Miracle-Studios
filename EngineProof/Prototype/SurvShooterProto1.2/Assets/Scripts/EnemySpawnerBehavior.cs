using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemySpawnerBehavior : MonoBehaviour
{
    public List<GameObject> ListOfEnemies;
    public GameObject spawnpoint;
    public float spawnTimer;
    float spawn;
    SpriteRenderer sr;
    public int maxEnemyCount;
    int enemycount;

    GameControllerBehavior gc;
    UIMenu ui;
    SoundController sound;


    // Start is called before the first frame update
    void Start()
    {
        sr = GetComponent<SpriteRenderer>();
        gc = GameObject.Find("GameController")
            .GetComponent<GameControllerBehavior>();
        ui = GameObject.Find("GameController")
            .GetComponent<UIMenu>();
        sound = GameObject.Find("SoundController")
            .GetComponent<SoundController>();
        enemycount = maxEnemyCount;        
    }

    // Update is called once per frame
    void Update()
    {
        int type = Random.Range(0, ListOfEnemies.Count);

        if (!ui.Paused)
        {
            spawn += Time.deltaTime;
        }

        if (spawn > spawnTimer)
        {
            if (!sr.isVisible)
            {
                enemycount--;
            }
            Spawn(type);
        }
        
        if (enemycount == 0 && !sr.isVisible)
        {
            gc.EnemyCount--;
            Destroy(gameObject);
        }
    }

    void Spawn(int type)
    {
        sound.AdjustSFX(0.2f);
        sound.PlaySound(sound.SFXList[3]);
        Instantiate(ListOfEnemies[type], spawnpoint.transform.position, Quaternion.identity);
        spawn = 0;
    }
}