import { ActionComplete, DownloadProgress } from "./Progress";
import { WriteStream } from "fs";
const fs = window.require('fs') as typeof import('fs');


export class Downloader {
  static async downloadFile(from: string, to: string, onProgress: DownloadProgress = () => {}, onComplete: ActionComplete = () => {}) {
    const response = await fetch(from);
    if (!response.ok) {
      throw new Error('Download error.');
    }

    const inStream = response.body;
    const maxLength = parseInt(response.headers.get('Content-Length') || '0', 10);
    if (inStream) {
      const stream = inStream.getReader();
      const outStream: WriteStream = fs.createWriteStream(to);
      let downloadProgress = 0;
      try {
        while (true) {
          const { done, value } = await stream.read();
          if (done)
            break;
          downloadProgress += value.length;
          onProgress(downloadProgress, maxLength);
          if (outStream) {
            outStream.write(value);
          }
        }
      }
      finally {
        stream.releaseLock();
        onComplete(true);
      }
    }
  }
}