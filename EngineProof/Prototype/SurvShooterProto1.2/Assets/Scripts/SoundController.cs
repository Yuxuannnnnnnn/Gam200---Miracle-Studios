using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class SoundController : MonoBehaviour
{
    public List<AudioClip> BGMList;
    public List<AudioClip> SFXList;

    public GameObject SFXUnit;
    public GameObject BGMUnit;

    public Slider BGMSlider;
    public Slider SFXSlider;

    AudioSource sound;
    AudioSource BGM;

    // Start is called before the first frame update
    void Start()
    {
        sound = SFXUnit.GetComponent<AudioSource>();
        BGM = BGMUnit.GetComponent<AudioSource>();
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void PlaySound(AudioClip clip)
    {
        sound.clip = clip;
        sound.PlayOneShot(clip);
    }

    public void PlayBGM(AudioClip bgm)
    {
        BGM.clip = bgm;
        BGM.loop = true;
        BGM.Play();
    }

    public void AdjustBGM(float vol)
    {
        BGM.volume = vol;
    }

    public void AdjustBGM()
    {
        
        BGM.volume = BGMSlider.value;
    }

    public void AdjustSFX(float vol)
    {
        sound.volume = vol;
    }

    public void AdjustSFX()
    {
        sound.volume = SFXSlider.value;
    }
}
